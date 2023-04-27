#include <Arduino.h>

#define Buzzer  19 //Buzzer GPIO 

void setup() {
  digitalWrite(Buzzer, OUTPUT);
  analogWrite(Buzzer, 127);   //generates pwm of 50% duty cycle
}

void loop() {
  delay(1000);
  digitalWrite(Buzzer, LOW); //OFF
}
