#include <Arduino.h>

#define RED_LED D1
#define YELLOW_LED D2
#define GREEN_LED D3

void setup() {
  Serial.begin(9600);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  Serial.println("UTS LED");
  delay(1000);
}

void loop() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(YELLOW_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  Serial.println("LED Nyala");

  delay(1000);

  digitalWrite(RED_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  Serial.println("LED Mati");

  delay(1000);
}