#include <Adafruit_BMP085.h>
#include <Arduino.h>
#include <DHT.h>
#include <SPI.h>

#define DHTPIN D3
#define DHTTYPE DHT11

#define RED_LED D5
#define GREEN_LED D6
#define BLUE_LED D7

DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;

const int rain = A0;
int rainReading;

void setup() {
  Serial.begin(9600);
  Serial.println("UTS IoT - Live Weather Monitoring");

  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(rain, INPUT);

  dht.begin();
  if (!bmp.begin()) {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {
    }
  }

  delay(1000);
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (rainReading > 700 && t < 30) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(BLUE_LED, HIGH);
    Serial.print("Kelembapan = ");
    Serial.print(h);
    Serial.println("%");
    Serial.print("Suhu = ");
    Serial.print(t);
    Serial.println(F("°C"));

    rainReading = analogRead(rain);
    Serial.print("Nilai Sensor Hujan = ");
    Serial.println(rainReading);

    Serial.print("Tekanan Udara = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    Serial.println("Cuaca Dingin dan Tidak Hujan");
  }

  else if (rainReading < 700 && t < 30) {
    digitalWrite(RED_LED, HIGH);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, LOW);
    Serial.print("Kelembapan = ");
    Serial.print(h);
    Serial.println("%");
    Serial.print("Suhu = ");
    Serial.print(t);
    Serial.println(F("°C"));

    rainReading = analogRead(rain);
    Serial.print("Nilai Sensor Hujan = ");
    Serial.println(rainReading);

    Serial.print("Tekanan Udara = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    Serial.println("Cuaca Dingin dan Hujan");
  }

  else if (rainReading > 700 && t >= 30) {
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(BLUE_LED, HIGH);
    Serial.print("Kelembapan = ");
    Serial.print(h);
    Serial.println("%");
    Serial.print("Suhu = ");
    Serial.print(t);
    Serial.println(F("°C"));

    rainReading = analogRead(rain);
    Serial.print("Nilai Sensor Hujan = ");
    Serial.println(rainReading);

    Serial.print("Tekanan Udara = ");
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");
    Serial.println("Cuaca Panas dan Tidak Hujan");
  }

  Serial.println();
  delay(2000);
}
