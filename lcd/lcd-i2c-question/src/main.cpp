#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(9600);
  // initialize LCD
  lcd.init();
  // turn on LCD backlight
  lcd.backlight();
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

void loop() {
  // set cursor to two column, first row
  lcd.setCursor(1, 0);

  lcd.home();

  // Print DateTime to the screen
  // untuk menampilkan datetime masih cara manual karena tidak memiliki
  // perangkat tambahan yaitu RTC Module salah satunya DS3231 ->
  // https://somtips.com/set-time-on-ds3231-real-time-clock-with-arduino-uno/
  lcd.print("31-03-2021 20:45");

  // Print scrolling message
  scrollText(1, ("Reza Rinaldi - IoT Polinema"), 1000, 16);

  delay(2000);
}