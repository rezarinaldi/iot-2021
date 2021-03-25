#include <Arduino.h>

#define RED_LED D5    // led warna merah
#define GREEN_LED D6  // led warna hijau
#define LED_BUILTIN 2 // led warnah biru (internal)

void setup() {
  Serial.begin(9600);
  // atur pin-pin digital sebagai output
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.println("Contoh Program LED SOS (Tugas)");
}

void loop() {
  // 3 dits (3 titik atau huruf S)
  for (int x = 0; x < 3; x++) {
    digitalWrite(GREEN_LED, HIGH); // LED nyala
    delay(150);                    // delay selama 150ms
    digitalWrite(GREEN_LED, LOW);  // LED mati
    Serial.println("LED Merah berkedip");
    delay(100); // delay selama 100ms
  }
  delay(100);

  // 3 dahs (3 garis atau huruf O)
  for (int x = 0; x < 3; x++) {
    digitalWrite(GREEN_LED, HIGH); // LED nyala
    delay(400);                    // delay selama 400ms
    digitalWrite(GREEN_LED, LOW);  // LED mati
    delay(100);                    // delay selama 100ms
  }

  // 100ms delay to cause slight gap between letters
  delay(100);
  // 3 dits again (3 titik atau huruf S)
  for (int x = 0; x < 3; x++) {
    digitalWrite(GREEN_LED, HIGH); // LED nyala
    delay(150);                    // delay selama 150ms
    digitalWrite(GREEN_LED, LOW);  // LED mati
    delay(100);                    // delay selama 100ms
  }

  // wait 5 seconds before repeating the SOS signal
  delay(5000);

  // 3 dits (3 titik atau huruf S)
  for (int x = 0; x < 3; x++) {
    digitalWrite(RED_LED, HIGH); // LED nyala
    delay(150);                  // delay selama 150ms
    digitalWrite(RED_LED, LOW);  // LED mati
    Serial.println("LED Hijau berkedip");
    delay(100); // delay selama 100ms
  }
  delay(100);

  // 3 dahs (3 garis atau huruf O)
  for (int x = 0; x < 3; x++) {
    digitalWrite(RED_LED, HIGH); // LED nyala
    delay(400);                  // delay selama 400ms
    digitalWrite(RED_LED, LOW);  // LED mati
    delay(100);                  // delay selama 100ms
  }

  // 100ms delay to cause slight gap between letters
  delay(100);
  // 3 dits again (3 titik atau huruf S)
  for (int x = 0; x < 3; x++) {
    digitalWrite(RED_LED, HIGH); // LED nyala
    delay(150);                  // delay selama 150ms
    digitalWrite(RED_LED, LOW);  // LED mati
    delay(100);                  // delay selama 100ms
  }

  // wait 5 seconds before repeating the SOS signal
  delay(5000);

  // 3 dits (3 titik atau huruf S)
  for (int x = 0; x < 3; x++) {
    digitalWrite(LED_BUILTIN, HIGH); // LED nyala
    delay(150);                      // delay selama 150ms
    digitalWrite(LED_BUILTIN, LOW);  // LED mati
    Serial.println("LED Biru (internal) berkedip");
    delay(100); // delay selama 100ms
  }
  delay(100);

  // 3 dahs (3 garis atau huruf O)
  for (int x = 0; x < 3; x++) {
    digitalWrite(LED_BUILTIN, HIGH); // LED nyala
    delay(400);                      // delay selama 400ms
    digitalWrite(LED_BUILTIN, LOW);  // LED mati
    delay(100);                      // delay selama 100ms
  }

  // 100ms delay to cause slight gap between letters
  delay(100);
  // 3 dits again (3 titik atau huruf S)
  for (int x = 0; x < 3; x++) {
    digitalWrite(LED_BUILTIN, HIGH); // LED nyala
    delay(150);                      // delay selama 150ms
    digitalWrite(LED_BUILTIN, LOW);  // LED mati
    delay(100);                      // delay selama 100ms
  }

  // wait 5 seconds before repeating the SOS signal
  delay(5000);

  Serial.println();
}