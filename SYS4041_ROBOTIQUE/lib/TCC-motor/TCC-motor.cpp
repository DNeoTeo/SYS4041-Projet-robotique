#include <TCC-motor.h>


void init_motorAB(){
  pinMode(pinMotorDir_A, OUTPUT);
  pinMode(pinMotorPWM_A, OUTPUT);
  pinMode(pinMotorDir_B, OUTPUT);
  pinMode(pinMotorPWM_B, OUTPUT);
}

void motorA_setDir(bool dir){ //HIGH en avant LOW en arrière
  digitalWrite(pinMotorDir_A, dir);
}

void motorA_setPWM(int pwm){
  digitalWrite(pinMotorPWM_A, pwm);
}
void motorB_setDir(bool dir){
  digitalWrite(pinMotorDir_B, dir);
}
void motorB_setPWM(int pwm){
  digitalWrite(pinMotorDir_B, pwm);
}