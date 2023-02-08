/*-----------------------------------------
					   Timer
				Sylvain BERTRAND, 2015
-----------------------------------------*/

#include "Arduino.h"
#include "timer.h"
#include "math.h"

// delay in seconds
Timer::Timer(double delay){
	_timeOfLastReset = millis()/1000.0;
	_delay = delay;
}


double Timer::getTimeOfLastReset(){
	return _timeOfLastReset;
}

double Timer::getDelay(){
	return _delay;
}
	
void Timer::setTimeOfLastReset(const double timeOfLastReset){
	_timeOfLastReset = timeOfLastReset;
}

void Timer::setDelay(const double delay){
	_delay = delay;
}


int Timer::checkTimeOut(){

	// if timer expired
	if ( ( (millis()/1000.0) -_timeOfLastReset) >_delay){
		
		// if timer expired several times
		// => reset to the integer part of the number of timer periods from last reset of the timer
		_timeOfLastReset = _timeOfLastReset + _delay*floor( (millis()/1000.0 - _timeOfLastReset) / _delay);
				
		return 1;
	} 
	else {
		return 0;
	}
}


double Timer::getRemainingTime(){
	// returns remaining time in seconds until expiration of the timer (value >0)
	// returns overtime if timer expired (value <0)
	return _delay - ( (millis()/1000.0) -_timeOfLastReset);
}


void Timer::reset(){
	_timeOfLastReset = millis()/1000.0;
}