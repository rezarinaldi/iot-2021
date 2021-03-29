#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
RTC_DS3231 rtc;

char t[32];

void setup() {
  Serial.begin(9600);
  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
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
  // set cursor to first column, first row
  lcd.setCursor(1, 0);

  lcd.home();

  // Print DateTime to the screen
  DateTime now = rtc.now();
  sprintf(t, "%02d-%02d %02d:%02d", now.day(), now.month(), now.hour(),
          now.minute());
  lcd.print(t);

  // Print scrolling message
  scrollText(1, ("Reza Rinaldi - Polinema 2021"), 250, 16);

  delay(2000);
}