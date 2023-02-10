#include <Arduino.h>
//#include <HUSKYLENS.h>
#include "TCC-motor.h"
#include "TCC-Huskylens.h"
#include "TCC-Tag.h"


/********** Constante - Variables globales *********/
//HUSKYLENS huskylens; //HUSKYLENS green line >> SDA; blue line >> SCL
TCC_Huskylens huskylens;
TCC_Motor motor;
TCC_Tag tag;

#define MAX_HEIGHT_ARUCO 180
// Variables
  enum state_e {
    IDLE,
    START,
    LOOK_FOR_TAG,
    TAG,
    STOP
  };

  state_e state = IDLE;
  long last_millis;
  int TagNbr = 0;

/********** Functions *********/
bool delayState (int delaytime);
void newState(state_e newE);


void stateMachine();

/********** Setup *********/
void setup() {
    Serial.begin(115200);
    huskylens.setup();
    motor.init_motorAB();
}

/********** Loop *********/
void loop() {
    stateMachine();
    tag.followTag(2, 160, 180);

}


/********** State Machine *********/
void stateMachine() {
  // Switch case
  switch (state)
  {
    case IDLE :
      //faut checker la couleur si c'est vert on va dans START
      motor.cmd_robot(0,0);
      if (huskylens.isColor(2)) {
        newState(START);
      }
      break;

    case START :
      //c'est vert, on démarre et on va dans look for tag
      TagNbr = 7;
      motor.cmd_robot(255,0);
      if(delayState(800)) {
        motor.cmd_robot(0,0);
      }
      huskylens.huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);
      if(delayState(1000)) {
        newState(LOOK_FOR_TAG);
      }
      break;
    
    case LOOK_FOR_TAG :
      // on cherche le tag
      motor.cmd_robot(0, 0);
      if(huskylens.isTag(TagNbr) && delayState(100)) {
        newState(TAG);
      }
      
      break;
    
    case TAG :
      //on incrémente et on revient dans look for tag
       switch (TagNbr)
      {
      case 1:
        /* code */
        break;
      
      default:
        break;
      }
      tag.followTag(TagNbr, 160, MAX_HEIGHT_ARUCO);
      if (TagNbr <= 7) {
        tag.followTag(TagNbr, 160, MAX_HEIGHT_ARUCO);
        if(huskylens.getTag(TagNbr).height >= MAX_HEIGHT_ARUCO){
          newState(LOOK_FOR_TAG);
          TagNbr ++;
        }
      }
      else {
          newState(STOP);
      }
      
      break;

    case STOP :
    // on a trouvé tous les tags donc on s'arrête
      motor.cmd_robot(0,0);
      break;

    default:
        break;
  }
}

void newState (state_e newE) {
    state = newE;
    last_millis = millis();
}

bool delayState(int delaytime){
    return((int)(millis()-last_millis)>= delaytime);
}
