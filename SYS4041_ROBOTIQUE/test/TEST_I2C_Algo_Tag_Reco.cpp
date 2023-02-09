#include <Arduino.h>
#include "HUSKYLENS.h"

enum state_e {
    IDLE,
    TURN,
    FORWARD
};

state_e state = IDLE;
long last_millis;

switch (state){
case IDLE :
    cmd_robot(0,0);
    if (isTag(1)) {
        newState(TURN);
    }
    if(isTag(2)) {
        newState(FORWARD);
    }
    break;

    case TURN :
        cmd_robot(0,255);
        if(delayState(1000)) {
            newState(IDLE);
        }
        break;

default:
    break;
}


void newState (state new) {
    //Serial.println(new);
    state = new;
    last.millis = millis();
}

bool delayState(int delaytime){
    return((millis().last.millis)>= delaytime);
}