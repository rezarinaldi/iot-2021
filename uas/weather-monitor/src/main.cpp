#include <Arduino.h>
#include <DHT.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <SFE_BMP180.h>
#include <WiFiClient.h>
#include <Wire.h>

#include "index.h" //Our HTML dashboard page

#define LED D6
#define DHTPIN D3
#define DHTTYPE DHT11
#define ALTITUDE 624 // Your Altitude in meters search in google

// Firebase
#define FIREBASE_HOST "weatherapp-1ae5b-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "JnOlO9ozkVM1Dycog3mFDRMI4iTOMIuByUOGqVZ4"

SFE_BMP180 pressure;

DHT dht(DHTPIN, DHTTYPE);

// SSID and Password of your WiFi router
const char *ssid = "p";
const char *password = "8karakter";

ESP8266WebServer server(80); // Server on port 80

void handleRoot() {
  server.send(200, "text/html", MAIN_page); // Send web page
}

float h, t;
const int rain = A0;

void handleADC() {
  char status;
  double T, P, p0, a;
  double Tdeg, Tfar, phg, pmb;

  status = pressure.startTemperature();
  if (status != 0) {
    // Wait for the measurement to complete:
    delay(status);
    status = pressure.getTemperature(T);
    if (status != 0) {
      // Print out the measurement:
      Serial.print("Temperature (bmp180): ");
      Serial.print(T, 2);
      Tdeg = T;
      Serial.print(" °C, ");
      Tfar = (9.0 / 5.0) * Tdeg + 32.0;
      Serial.print(Tfar * Tdeg + 32.0, 2);
      Serial.println(" °F");

      status = pressure.startPressure(3);
      if (status != 0) {
        // Wait for the measurement to complete:
        delay(status);
        status = pressure.getPressure(P, T);
        if (status != 0) {
          // Print out the measurement:
          Serial.print("Absolute pressure: ");
          Serial.print(P, 2);
          pmb = P;
          Serial.print(" mb, ");
          phg = pmb * 0.0295333727;
          Serial.print(phg, 2);
          Serial.println(" inHg");

          p0 = pressure.sealevel(P, ALTITUDE);
          Serial.print("Relative (sea-level) pressure: ");
          Serial.print(p0, 2);
          Serial.print(" mb, ");
          Serial.print(p0 * 0.0295333727, 2);
          Serial.println(" inHg");

          a = pressure.altitude(P, p0);
          Serial.print("Computed altitude: ");
          Serial.print(a, 0);
          Serial.print(" meters, ");
          Serial.print(a * 3.28084, 0);
          Serial.println(" feet");
        } else
          Serial.println("error retrieving pressure measurement\n");
      } else
        Serial.println("error starting pressure measurement\n");
    } else
      Serial.println("error retrieving temperature measurement\n");
  } else
    Serial.println("error starting temperature measurement\n");

  h = dht.readHumidity();
  t = dht.readTemperature();

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println("°C");
  
  int rainReading = analogRead(rain);
  Serial.print("Rain: ");
  Serial.println(rainReading);
  
  // Integer to string conversion sensors
  String firePmb = String(pmb) + String(" mb"); //PMB integer to string conversion
  String firePhg = String(phg) + String(" hg"); //PHG integer to string conversion
  String fireHumid = String(h) + String(" %"); //Humidity integer to string conversion
  String fireTemp = String(t) + String(" °C"); //Temperature integer to string conversion
  String fireRain = String(rainReading); //Rain integer to string conversion

  Serial.println();
  delay(2000);

  // Create JSON data
  String data = "{\"Rain\":\"" + String(rainReading) + "\", \"Pressuremb\":\"" +
                String(pmb) + "\", \"Pressurehg\":\"" + String(phg) +
                "\", \"Temperature\":\"" + String(t) + "\", \"Humidity\":\"" +
                String(h) + "\"}";

  digitalWrite(LED, !digitalRead(LED)); // Toggle LED on data request ajax
  server.send(200, "text/plane", data); // Send ADC value, temperature and
                                        // humidity JSON to client ajax request

  // Send string sensors to path firebase
  Firebase.pushString("/BMP180/Pressure (mb)", firePmb); //setup path to send PMB readings
  Firebase.pushString("/BMP180/Pressure (hg)", firePhg); //setup path to send PHG readings
  Firebase.pushString("/DHT11/Humidity", fireHumid); //setup path to send Humidity readings
  Firebase.pushString("/DHT11/Temperature", fireTemp); //setup path to send Temperature readings
  Firebase.pushString("/RAIN", fireRain); //setup path to send Rain readings
    if (Firebase.failed()) 
    {
      Serial.print("pushing /logs failed:");
      Serial.println(Firebase.error());
      return;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println();

  // Dht11 Sensor
  dht.begin();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // LED
  pinMode(LED, OUTPUT);

  // Rain Sensor
  pinMode(rain, INPUT);

  // BMP180 Sensor
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else {
    Serial.println("BMP180 init fail\n\n");
    while (1)
      ; // Pause forever.
  }

  WiFi.begin(ssid, password); // Connect to your WiFi network
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // If connection successful show IP address in serial monitor
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); // IP address assigned to your ESP

  // Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH); // connect to the firebase

  server.on("/", handleRoot); // Which routine to handle at root location. This
                              // is display page
  server.on("/readADC", handleADC); // This page is called by java Script AJAX

  server.begin(); // Start server
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Handle client requests
}
