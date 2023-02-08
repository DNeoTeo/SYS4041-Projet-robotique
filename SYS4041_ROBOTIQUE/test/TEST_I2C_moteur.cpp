#include <Arduino.h>
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
    digitalWrite(PWMA, HIGH);
    digitalWrite(DIRA, HIGH);
    digitalWrite(PWMB, HIGH);
    digitalWrite(DIRB, HIGH);
}