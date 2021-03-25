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
  float converted = 0.00; // variabel konversi dalam satuan kelvin dan reamur

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

  // rumus konversi dalam satuan kelvin
  converted = t + 273.15;
  Serial.print(converted);
  Serial.print("K ");

  // rumus konversi dalam satuan reamur
  converted = t * 0.8;
  Serial.print(converted);
  Serial.print("°R ");

  Serial.print(f);
  Serial.print(F("°F Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  delay(2000);
}