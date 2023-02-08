/*-----------------------------------------
					   Timer
				Sylvain BERTRAND, 2015
-----------------------------------------*/

#ifndef TIMER_H
#define TIMER_H

class Timer
{
	private:
		double _timeOfLastReset; // in seconds
		double _delay; // in seconds
	
	public:
		Timer(double delay); // delay in seconds

		double getTimeOfLastReset();
		double getDelay();
	
		void setTimeOfLastReset(const double timeOfLastReset);
		void setDelay(const double delay);
	
	
		int checkTimeOut();  // returns 1 if timer out, 0 else
		double getRemainingTime(); // returns remaining time in seconds until expiration of the timer (return negative value if timer already expired. the value corresponds to the overtime)
		void reset(); // reset timer

};





#endif