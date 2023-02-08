/*-----------------------------------------
					Motor control
				Sylvain BERTRAND, 2015
-----------------------------------------*/

#include <timer.h>

Timer timer1(0.25); // delay: 0.25s
Timer timer2(1.0); // delay: 1s

void setup() {  
  
  Serial.begin (9600);

    timer1.reset(); 
  timer2.reset(); 
} 


void loop(){ 
  
  if (timer1.checkTimeOut()){
    Serial.print(millis()/1000.0);
    Serial.println(" - timer 1 - Time out");
  }
  
  if (timer2.checkTimeOut()){
    Serial.print(millis()/1000.0);
    Serial.println(" -- timer 2 - Time out");
  }
  
  //Serial.println(timer1.getRemainingTime());
  
}