#include "RTClib.h"
#include <LiquidCrystal.h>
#include <Wire.h>
#include <ezButton.h>

// LCD module connections (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(5,6,7,8,9,10);

//Variables
RTC_DS1307 rtc;
int enA = 26;
int cw = 24;
int ccw = 22;
int speeD = 255;
int lastButtonState;
int currentButtonState;
int num = 0;
const int BUTTON_PIN = 40;
ezButton button(BUTTON_PIN);


void setup() {
  rtc.begin();
  lcd.begin(16, 2);

  //Fan Setup
  pinMode(enA, OUTPUT);
  pinMode(cw, OUTPUT);
  pinMode(ccw, OUTPUT);
  analogWrite(enA, speeD);
  
}
void loop() {
  
  //Print row 1
  DateTime now = rtc.now();
  DateTime real (now + TimeSpan(0,1,-10,-30));
  lcd.setCursor(0,0);
  lcd.print("Time: ");
  lcd.print(real.hour(),DEC);
  lcd.print(":");
  lcd.print(real.minute(),DEC);
  lcd.print(":");
  lcd.print(real.second(),DEC);
  delay(1000);

  //Print row 2
  lcd.setCursor(0,1);
  lcd.print("RPM:Full");
  lcd.print(" Rot:");
  lastButtonState = currentButtonState;
  currentButtonState = digitalRead(BUTTON_PIN);

  //Button States
  if(lastButtonState == HIGH && currentButtonState == LOW) {
    num++;
  }
  if(num % 2 == 0) {
    digitalWrite(cw, HIGH);
    digitalWrite(ccw, LOW);
    lcd.print("CW");
    
  }
  else {
    digitalWrite(cw, LOW);
    digitalWrite(ccw, HIGH);
    lcd.print("CC");
  }
}
