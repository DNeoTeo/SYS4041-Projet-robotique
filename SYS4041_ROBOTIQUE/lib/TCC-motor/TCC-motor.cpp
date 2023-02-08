#include <TCC-motor.h>
#include "Arduino.h"

void init_motorAB(){
    pinMode(pinMotorDir_A, OUTPUT);
    pinMode(pinMotorPWM_A, OUTPUT);
    pinMode(pinMotorDir_B, OUTPUT);
    pinMode(pinMotorPWM_B, OUTPUT);
}

void motorA_setDir(bool dir){ //HIGH en avant LOW en arrière
    digitalWrite(pinMotorDir_A, dir);
}

void motorA_setPWM(int pwm){ //0-255 pour choisir entre moteur arrêt jusqu'à moteur alimenté en puissance max
    analogWrite(pinMotorPWM_A, pwm);
}
void motorB_setDir(bool dir){
    digitalWrite(pinMotorDir_B, dir);
}
void motorB_setPWM(int pwm){
    analogWrite(pinMotorDir_B, pwm);
}

void cmd_motors(int pwmD, int pwmG){
    digitalWrite(pinMotorDir_A, (pwmG>0));
    analogWrite(pinMotorPWM_A, (pwmG>0)?pwmG:(-pwmG));
    digitalWrite(pinMotorDir_B, (pwmD>0));
    analogWrite(pinMotorPWM_B, (pwmD>0)?pwmD:(-pwmD));
}

void cmd_robot(int lineaire, int angulaire){
    cmd_motors(((lineaire-angulaire)>>1), ((lineaire+angulaire)>>1));
}
