#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <SFE_BMP180.h>
#include <Wire.h>

String apiKey = "09KU5LB7HEE27U47";

const char *ssid = "p";         // Enter your WiFi Network's SSID
const char *pass = "8karakter"; // Enter your WiFi Network's Password
const char *server = "api.thingspeak.com";

WiFiClient client;

#define RED_LED D5
#define GREEN_LED D6
#define BLUE_LED D7
int buzzer = D3;
int rain = D4;

#define ALTITUDE 624 // Your Altitude in meters search in google
SFE_BMP180 pressure;

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(rain, INPUT);

  // WiFi
  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // BMP180 Sensor
  if (pressure.begin())
    Serial.println("BMP180 init success");
  else {
    Serial.println("BMP180 init fail\n\n");
    while (1)
      ; // Pause forever.
  }
  delay(1000);
}

void loop() {
  int waterLevel = analogRead(A0);

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

  if (waterLevel <= 60) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(buzzer, LOW);
    Serial.print("Sensor Hujan: ");
    Serial.println(rain);
    Serial.print("Sensor Ketinggian Air: ");
    Serial.println(waterLevel);
    Serial.println("Ketinggian Air Kosong");
    Serial.println("Tidak Hujan");
    Serial.println();
    delay(100);
  } else if (waterLevel > 250 && waterLevel <= 340) {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(buzzer, LOW);
    Serial.print("Sensor Hujan: ");
    Serial.println(rain);
    Serial.print("Sensor Ketinggian Air: ");
    Serial.println(waterLevel);
    Serial.println("Ketinggian Air Rendah");
    Serial.println("Hujan Gerimis");
    Serial.println();
    delay(100);
  } else if (waterLevel > 350 && waterLevel <= 390) {
    digitalWrite(BLUE_LED, LOW);
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(buzzer, LOW);
    Serial.print("Sensor Hujan: ");
    Serial.println(rain);
    Serial.print("Sensor Ketinggian Air: ");
    Serial.println(waterLevel);
    Serial.println("Ketinggian Air Sedang");
    Serial.println("Hujan Sedang");
    Serial.println();
    delay(100);
  } else if (waterLevel > 400 && waterLevel <= 450 && digitalRead(rain) == 1) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    digitalWrite(buzzer, HIGH);
    Serial.print("Sensor Hujan: ");
    Serial.println(rain);
    Serial.print("Sensor Ketinggian Air: ");
    Serial.println(waterLevel);
    Serial.println("Ketinggian Air Tinggi");
    Serial.println("Hujan Deras");
    Serial.println("Buzzer Menyala");
    Serial.println();
  }
  delay(1500);

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(P);
    postStr += "&field2=";
    postStr += String(waterLevel);
    postStr += "&field3=";
    postStr += String(rain);
    postStr += "\r\n\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);
  }

  client.stop();
  Serial.println("Sending....");
  delay(1500);
}