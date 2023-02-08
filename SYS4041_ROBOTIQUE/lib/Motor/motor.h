/*-----------------------------------------
					Motor control
				Sylvain BERTRAND, 2015
-----------------------------------------*/


#ifndef MOTOR_H
#define MOTOR_H

// PINs definition on motor shield

// red Ardumoto shield
/*
#define leftMotorPWMPin 3
#define leftMotorDirPin 12
#define rightMotorPWMPin 11
#define rightMotorDirPin 13
 */
  
 // blue motorShield
 // motor A
#define leftMotorPwmPin 6
#define leftMotorDirPin 7
// motor B
#define rightMotorPwmPin 9
#define rightMotorDirPin 8 
  
  
// motor class
class Motor
{	
  private:
	unsigned int _pwmPin;
	unsigned int _dirPin;
	int _u;   // control value: integer between -200 (backward full speed) and +200 (forward full speed)
  
  
  public:
	
	Motor(int pwmPin, int dirPin);
	
	unsigned int getPwmPin();
	unsigned int getDirPin();
	int getU();
	void setPwmPin(unsigned int pin);
	void setDirPin(unsigned int pin);
	void setU(int u);
	
	void stop();
  

};
 
#endif
