#include <Arduino.h>
#include <DHT.h>

#define sensorLDR A0
#define RED_LED D5
#define BLUE_LED D6
#define DHTTYPE DHT11

DHT dht(D2, DHTTYPE);

int nilaiSensor, celcius;

void biruKedip() {
  digitalWrite(BLUE_LED, LOW);
  delay(500);
  digitalWrite(BLUE_LED, HIGH);
  delay(500);
}

void setup() {
  Serial.begin(9600);
  // atur pin-pin digital sebagai output
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  Serial.println("Tugas penggunaan sensor LDR, LED dan DHT");
  dht.begin();
  delay(3000);
}

void loop() {
  delay(2000);
  digitalWrite(RED_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
  float t = dht.readTemperature();
  nilaiSensor = analogRead(sensorLDR);

  if (isnan(t)) {
    Serial.println("Failed to read from DHT Sensor!");
    return;
  }

  if (t < 0) {
    celcius = t * -1;
  } else {
    celcius = t;
  }

  if (t < 27.30 && nilaiSensor > 800) {
    biruKedip();
    Serial.print("Nilai Sensor LDR: ");
    Serial.println(nilaiSensor);
    Serial.print("Nilai Temperatur: ");
    Serial.print(celcius);
    Serial.println(F("°C "));
    Serial.println("Cahaya redup dan Suhu dingin");
    Serial.println("Lampu LED Biru berkedip");
  } else if (t > 27.60 && nilaiSensor < 400) {
    digitalWrite(RED_LED, LOW);
    Serial.print("Nilai Sensor LDR: ");
    Serial.println(nilaiSensor);
    Serial.print("Nilai Temperatur: ");
    Serial.print(celcius);
    Serial.println(F("°C "));
    Serial.println("Cahaya terang dan Suhu panas");
    Serial.println("Lampu LED Merah menyala");
  }
}