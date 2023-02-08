/*-----------------------------------------
					Motor control
				Sylvain BERTRAND, 2015
-----------------------------------------*/

#include <motor.h>

// left and right motors with corresponding pins
Motor leftMotor(leftMotorPwmPin, leftMotorDirPin);
Motor rightMotor(rightMotorPwmPin, rightMotorDirPin);

// global variables
int uL = 0;
int uR = 0;
int leftInc = 10;
int rightInc = 10;


// ************** SETUP *********************
void setup() {
  Serial.begin(9600);
 
}
// *******************************************


// *************** LOOP **********************
void loop() {


uL = 100;
uR = 100;
leftMotor.setU(uL);
rightMotor.setU(uR);

delay(5000);

leftMotor.stop();
rightMotor.stop();

delay(5000);

  
/*
  
uL=uL+leftInc;

if (uL>200){
  uL=200;
  leftInc=-10;
}
if (uL<-200){
  uL=-200;
  leftInc=10;
}

uR = uR + rightInc;

if (uR>200){
  uR=200;
  rightInc=-10;
}
if (uR<-200){
  uR=-200;
  rightInc=10;
}  

// apply control values to motors
leftMotor.setU(uL);
rightMotor.setU(uR);

// send values through serial
Serial.print("Motor control values:   Left: ");
Serial.print(leftMotor.getU());
Serial.print("  Right : ");
Serial.print(rightMotor.getU());
Serial.println();
  
// pause
delay(250);
*/  
  
}
// *******************************************




