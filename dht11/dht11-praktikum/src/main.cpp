#include <Arduino.h>
#include <DHT.h>

#define DHTTYPE DHT11
DHT dht(D2, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Praktikum sensor suhu dan kelembaban menggunakan DHT11");
  dht.begin();
}

void loop() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Kelembaban udara: "));
  Serial.print(h);
  Serial.print(F("% Suhu: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  delay(2000);
}