#include <Arduino.h>

#define sensorLDR A0
#define RED_LED D5
#define GREEN_LED D6
#define BLUE_LED D7

int nilaiSensor;

void ledNyala() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void ledMati() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
}

void setup() {
  Serial.begin(9600);
  // atur pin-pin digital sebagai output
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  Serial.println("Tugas penggunaan sensor LDR dan LED");
  delay(3000);
}

void loop() {
  nilaiSensor = analogRead(sensorLDR);

  if (nilaiSensor > 800) {
    Serial.print("Nilai sensor LDR: ");
    Serial.println(nilaiSensor);
    Serial.println("Cahaya ruangan redup");
    Serial.println("Lampu LED Nyala");
    ledNyala();
  } else if (nilaiSensor < 400) {
    Serial.print("Nilai sensor LDR: ");
    Serial.println(nilaiSensor);
    Serial.println("Cahaya ruangan terang");
    Serial.println("Lampu LED Mati");
    ledMati();
  }
  delay(1000);
}