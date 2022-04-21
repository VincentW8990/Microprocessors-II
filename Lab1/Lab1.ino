/*
 * EECE.4520 Microprocessor II and Embedded System Design
 * University of Massachusetts Lowell
 * Lab 1: Traffic Light Controller
 * by Tenlong Hwong & Vincent Wong
 */

//Components
int GREEN = 5;    //Green LED connected to pin 5
int YELLOW = 4;   //Yellow LED connected to pin 4
int RED = 3;    //Red LED connected to pin 3
int buzzer = 9;   //Buzzer connected to pin 9

//Delays
int DELAY_17s = 17000;    //17s delay
int DELAY_SEC = 1000;   //1s delay
int DELAY_3s = 3000;    //3s delay

//Button
int BUTTON_PIN = 7;
int lastButtonState;    // the previous state of button
int currentButtonState; // the current state of button
int ledState = LOW;

void setup() {
  //Setup components
  pinMode(RED, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  currentButtonState = digitalRead(BUTTON_PIN);
}

void loop() {
  lastButtonState = currentButtonState;   // save the last state
  currentButtonState = digitalRead(BUTTON_PIN); /// read new state
  digitalWrite(RED, LOW);
  delay(DELAY_SEC);
  digitalWrite(RED, HIGH);
  delay(DELAY_SEC);
  //Detect Button push
  if(lastButtonState == HIGH && currentButtonState == LOW) {
    // toggle state of LED
    ledState = !ledState;
    // Jump to the traffic light loop (red, green, yellow, ...)
    red_light();
  }
}
void red_light()
{
  digitalWrite(RED, HIGH);    //Turn LED on
  delay(DELAY_17s);   //Stay on for 17s
  ring();   //Stay on for 3s while also ringing
  digitalWrite(RED, LOW);   //Turn LED off
  green_light();    //Swich to green
}
void green_light()
{
  digitalWrite(GREEN, HIGH);
  delay(DELAY_17s);
  ring();
  digitalWrite(GREEN, LOW);
  yellow_light();   //Switch to yellow
}
void yellow_light()
{
  //Yellow stays on for 3s
  digitalWrite(YELLOW, HIGH);
  delay(DELAY_3s);

  //Yellow blinks for 3s (beeps at the same time to indicate color switch)
  tone(buzzer, 1000);   //ring for the following 3s  
  digitalWrite(YELLOW, LOW);
  delay(DELAY_SEC);
  digitalWrite(YELLOW, HIGH);
  delay(DELAY_SEC);
  digitalWrite(YELLOW, LOW);
  delay(DELAY_SEC);
  digitalWrite(YELLOW, HIGH);
  noTone(buzzer);
  digitalWrite(YELLOW, LOW);
  red_light();    //Switch to red
}
void ring()   //3s buzzer
{
  tone(buzzer, 1000); // Send 1KHz sound signal...
  delay(DELAY_3s);        // ...for 3 sec
  noTone(buzzer);     // Stop sound...
}