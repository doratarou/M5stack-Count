#include <Arduino.h>
#include <M5Stack.h>
void setup() {
  // put your setup code here, to run once:
  M5.begin();
  M5.Lcd.clear(BLACK);
  M5.Lcd.setTextSize(3);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setCursor(10,100);
  M5.Lcd.print("00");
  M5.Lcd.print(":");
  M5.Lcd.println("00");
}

void loop() {
  // put your main code here, to run repeatedly:
}