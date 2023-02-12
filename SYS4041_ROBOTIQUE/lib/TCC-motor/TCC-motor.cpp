/*********** TCC-Motor class ***********/

#include "TCC-motor.h"
#include "Arduino.h"

/********** Constructor **********/
TCC_Motor::TCC_Motor() {}


/********** Initialise all the pins **********/ 
void TCC_Motor::setup(){
    pinMode(pinMotorDir_A, OUTPUT);
    pinMode(pinMotorPWM_A, OUTPUT);
    pinMode(pinMotorDir_B, OUTPUT);
    pinMode(pinMotorPWM_B, OUTPUT);
}


/********** Motor A **********/
void TCC_Motor::motorA_setDir(bool dir){ //HIGH en avant LOW en arrière
    digitalWrite(pinMotorDir_A, dir);
}

void TCC_Motor::motorA_setPWM(int pwm){ //0-255 pour choisir entre moteur arrêt jusqu'à moteur alimenté en puissance max
    analogWrite(pinMotorPWM_A, pwm);
}


/********** Motor B **********/
void TCC_Motor::motorB_setDir(bool dir){
    digitalWrite(pinMotorDir_B, dir);
}

void TCC_Motor::motorB_setPWM(int pwm){
    analogWrite(pinMotorDir_B, pwm);
}


/********** Control the motor **********/
void TCC_Motor::cmd_motors(int pwmD, int pwmG){
    digitalWrite(pinMotorDir_A, (pwmG>0));
    analogWrite(pinMotorPWM_A, (pwmG>0)?pwmG:(-pwmG));
    digitalWrite(pinMotorDir_B, (pwmD>0));
    analogWrite(pinMotorPWM_B, (pwmD>0)?pwmD:(-pwmD));
}


/********** Control the robot's direction **********/
void TCC_Motor::cmd_robot(int lineaire, int angulaire){
    cmd_motors(((lineaire-angulaire)>>1), ((lineaire+angulaire)>>1));
}