/*-----------------------------------------
					Motor control
				Sylvain BERTRAND, 2015
-----------------------------------------*/


//#include "WProgram.h"
#include "Arduino.h"
#include "Motor.h"


Motor::Motor(int pwmPin, int dirPin){
	_pwmPin = pwmPin;
	_dirPin = dirPin;
	pinMode(_pwmPin, OUTPUT);
	pinMode(_dirPin, OUTPUT);
	this->setU(0);  
}


unsigned int Motor::getPwmPin(){
	return _pwmPin;
}

unsigned int Motor::getDirPin(){
	return _dirPin;
}

int Motor::getU(){
	return _u;
}

void Motor::setPwmPin(unsigned int pin){
	_pwmPin = pin;
	pinMode(_pwmPin, OUTPUT);
}

void Motor::setDirPin(unsigned int pin){
	_dirPin = pin;
	pinMode(_dirPin, OUTPUT);
}

void Motor::setU(int u){  
// compute PWM and direction values from u (integer between -200 and +200)
// assign computed values on corresponding pwm and direction pins

	_u = u;
	
	// saturations
	if (_u>200)
		_u = 200;
	if (_u<-200)
		_u = -200;
	
	// write rotation speed module
	analogWrite(_pwmPin, abs(_u));

	// write rotation speed direction
	if (_u>0)
		digitalWrite(_dirPin, LOW);  // forward
	else
		digitalWrite(_dirPin, HIGH);  // backward
}


void Motor::stop(){
	this->setU(0);
}