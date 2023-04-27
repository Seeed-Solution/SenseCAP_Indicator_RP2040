#include <Arduino.h>

#define BEEP  19 //BEEP GPIO 

void setup() {
  digitalWrite(BEEP, OUTPUT);
  analogWrite(BEEP, 127);   //generates pwm of 50% duty cycle
}

void loop() {
  delay(1000);
  digitalWrite(BEEP, LOW); //OFF
}
