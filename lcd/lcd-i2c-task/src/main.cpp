#include <Arduino.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTTYPE DHT11
#define RED_LED D5   // led warna merah
#define GREEN_LED D6 // led warna hijau
#define BLUE_LED D7  // led warnah biru

DHT dht(D3, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  Serial.println("Tugas sederhana menggunakan DHT11, LED RGB, dan LCD.");
  dht.begin();
  lcd.init(); // initialize the lcd
  lcd.backlight();
  pinMode(RED_LED, OUTPUT); // atur pin-pin digital sebagai output
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  lcd.print("Loading.....");
  lcd.home();
}

void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i = 0; i < lcdColumns; i++) {
    message = " " + message;
  }
  message = message + " ";
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

void red() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
}

void green() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, HIGH);
}

void blue() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, LOW);
}

void dead() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
}

void loop() {
  delay(2000);

  float t = dht.readTemperature();
  float f = dht.readTemperature(true);

  if (t >= 29) {
    for (int i = 0; i < 3; i++) {
      red();
      Serial.println("Suhu saat ini panas");
      Serial.println("Lampu LED Merah berkedip");
      delay(150);
      dead();
      delay(150);
    }
  } else if (t <= 28.30) {
    for (int i = 0; i < 3; i++) {
      green();
      Serial.println("Suhu saat ini dingin");
      Serial.println("Lampu LED Hijau berkedip");
      delay(150);
      dead();
      delay(150);
    }
  } else {
    for (int i = 0; i < 3; i++) {
      blue();
      Serial.println("Suhu saat ini normal");
      Serial.println("Lampu LED Biru berkedip");
      delay(150);
      dead();
      delay(150);
    }
  }

  lcd.home();
  lcd.print(t);
  lcd.print("\337C|");
  lcd.print(f);
  lcd.print("\337F");
  // untuk menampilkan datetime masih cara manual karena tidak memiliki
  // perangkat tambahan yaitu RTC Module salah satunya DS3231 ->
  // https://somtips.com/set-time-on-ds3231-real-time-clock-with-arduino-uno/
  scrollText(1, "01-04-2021 03:40", 1000, 16);
}