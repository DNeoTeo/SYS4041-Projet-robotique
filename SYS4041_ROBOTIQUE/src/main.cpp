#include <Arduino.h>
#include <HUSKYLENS.h>
#include <motor.h>

#define PWMA    3
#define DIRA    2
#define PWMB    9
#define DIRB    8

void setup() {
    pinMode(PWMA, OUTPUT);
    pinMode(DIRA, OUTPUT);
    pinMode(PWMB, OUTPUT);
    pinMode(DIRB, OUTPUT);
}

void loop() {
  // PWM HIGH tourne, LOW arrêt
  //DIR HIGH avance, LOW recule
    digitalWrite(PWMA, HIGH);
    digitalWrite(DIRA, LOW);
    digitalWrite(PWMB, HIGH);
    digitalWrite(DIRB, HIGH);
}