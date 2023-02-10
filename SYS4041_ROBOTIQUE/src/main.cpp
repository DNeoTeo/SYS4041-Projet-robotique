#include <Arduino.h>
#include "TCC-motor.h"
#include "TCC-Huskylens.h"
#include "TCC-Tag.h"


/********** Constante - Variables globales **********/
// Variables
TCC_Huskylens huskylens;
TCC_Motor motor;
TCC_Tag tags;

#define MAX_HEIGHT_ARUCO 170
#define MAX_NB_TAG 7

  enum state_e {
    IDLE,
    START,
    LOOK_FOR_TAG,
    FOLLOW_TAG,
    TAG,
    STOP
  };

  state_e state = IDLE;
  long last_millis;
  int TagNbr = 0;

/********** Functions **********/
bool delayState (int delaytime);
void newState(state_e newE);
// void followTag(int IDTag, int consigneCentre, int consigneDist);


void stateMachine();

/********** Setup **********/
void setup() {
    Serial.begin(115200);
    huskylens.setup();
    motor.setup();
    tags.setup(huskylens, motor);
}

/********** Loop **********/
void loop() {
    stateMachine();
}


/********** State Machine **********/
void stateMachine() {
  // Switch case
  switch (state)
  {
    // Start state the robot is looking for the color
    case IDLE :
      //faut checker la couleur si c'est vert on va dans START
      motor.cmd_robot(0,0);
      if (true) { //huskylens.isColor(1)
        newState(START);
      }
      break;

    // The robot has found the right color, the race can start
    case START :
      // We setup everything for the tag search
      huskylens.huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);
      // First the robot look for the tag n°1
      TagNbr = 1;
      motor.cmd_robot(255,0);
      if(delayState(800)) {
        motor.cmd_robot(0,0);
      }
      if(delayState(1000)) {
        newState(TAG);
      }
      break;
    
    // The robot is looking around if it can find the right tag
    case LOOK_FOR_TAG :
      motor.cmd_robot(0, 60);
      if(huskylens.isTag(TagNbr)) {
        newState(FOLLOW_TAG);
      }
      break;
    
    // Once the right tag is found the robot will go towards it
    case FOLLOW_TAG : 
      // Did the robot found all the tags ? 
      //If no the robot continue to look for the other
      if (TagNbr <= MAX_NB_TAG){
        tags.followTag(TagNbr, 160, MAX_HEIGHT_ARUCO+30);
        int heightTAG = huskylens.getTag(TagNbr).height;
        //Serial.print("HEIGHT= ");
        Serial.println(heightTAG);
        if(heightTAG >= 140){
          TagNbr ++;
          newState(TAG);
        }
      }
      // If yes, the robot go to the state "stop"
      else{
        newState(STOP);
      }
    break;

    // Which tag is the robot looking for ?
    case TAG :
      // Each case is specifically created to optimise the direction of the robot 
      // When looking for the wanted tag
      switch (TagNbr)
      {
        case 1:
          motor.cmd_robot(255,0);
          if(delayState(1000)){
            newState(LOOK_FOR_TAG);
          }
          break;
        case 2:
          motor.cmd_robot(50,200);
          if(delayState(400)){
            newState(LOOK_FOR_TAG);
          }
          break;
        case 3:
          motor.cmd_robot(50,-200);
          if(delayState(400)){
            newState(LOOK_FOR_TAG);
          }
          break;
        case 4:
          /* code */
          break;
        case 5:
          /* code */
          break;
        case 6:
          /* code */
          break;
        case 7:

          break;
        default:
          newState(LOOK_FOR_TAG);
          break;
      }      
      break;

    // The robot found all the tag, the robot stop
    case STOP :
      motor.cmd_robot(0,0);
      break;


    default:
        break;
  }
}

/********** Function to change the state **********/
void newState (state_e newE) {
    state = newE;
    last_millis = millis();
}

/********** Delay for the state change - this delay doesn't pause the robot **********/
bool delayState(int delaytime){
    return((int)(millis()-last_millis)>= delaytime);
}