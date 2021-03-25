#include <Arduino.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Contoh Penggunaan Sensor LDR");
  delay(3000);
}

void loop() {
  int result = analogRead(A0);
  Serial.print("Nilai sensor: ");
  Serial.println(result);
  delay(1000);
}