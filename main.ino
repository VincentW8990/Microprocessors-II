#include <Wire.h>
#include <MPU6050.h>
int normx;
int normy;
MPU6050 mpu;
int buzzer = 7;

#define joyX A0
#define joyY A1
int xValue;
int yValue;
char letter;
char buz;
char currentLetter = 'z';
void setup() {
  Serial.begin(115200);
  mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G);
  mpu.getScale();
  pinMode(buzzer, OUTPUT);
}
 
void loop() {
  // put your main code here, to run repeatedly:
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  buz = Serial.read();
  //Serial.println(xValue);
  //Serial.println(yValue);
  if(xValue < 100) {
    letter = 'a';
  }
  else if(xValue > 900) {
    letter = 'd';
  }
  else if(yValue < 100) {
    letter = 'w';
  }
  else if(yValue > 900) {
    letter = 's';
  }

  Vector normGyro = mpu.readNormalizeGyro();
  normx = normGyro.XAxis;
  normy = normGyro.YAxis;
  
  if(normx > 30) {
    letter = 's';
    Serial.println(letter);
    delay(500);
  }
  else if(normx < -50) {
    letter = 'w';
    Serial.println(letter);
    delay(500);
  }
  else if(normy > 100) {
    letter = 'd';
    Serial.println(letter);
    delay(500);
  }
  else if(normy < -50) {
    letter = 'a';
    Serial.println(letter);
    delay(500);
  }
  if(currentLetter != letter) {
    Serial.println(letter);
    currentLetter = letter;
  }
  if(buz == 'b') {
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(500);        // ...for 3 sec
    noTone(buzzer);    
  }
  
}
