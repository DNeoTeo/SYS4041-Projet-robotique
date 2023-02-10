#include <Arduino.h>
#include "TCC-motor.h"
#include "TCC-Huskylens.h"
#include "TCC-Tag.h"


/********** Constante - Variables globales **********/
// Variables
TCC_Huskylens huskylens;
TCC_Motor motor;
TCC_Tag tags;

#define MAX_HEIGHT_ARUCO 200
#define MAX_NB_TAG 6

  enum state_e {
    IDLE,
    START,
    LOOK_FOR_TAG,
    STOP_LOOK,
    FOLLOW_TAG,
    TAG,
    STOP,
    VICTORY_DANCE
  };

  state_e state = START;
  long last_millis;
  int TagNbr = 0;
  int tmp;
  state_e nextState;
/********** Functions **********/
bool delayState (int delaytime);
void newState(state_e newE);


void stateMachine();

/********** Setup **********/
void setup() {
    Serial.begin(115200);
    huskylens.setup();
    motor.setup();
    tags.setup(huskylens, motor);
    tmp = 0;
    nextState = START;
    motor.cmd_robot(0,0);
}

/********** Loop **********/
void loop() {
    stateMachine();
}
int stateDance=1;
/********** State Machine **********/
void stateMachine() {
  // Switch case
  switch (state)
  {
    // Start state the robot is looking for the color
    case IDLE :
      if (delayState(tmp)) {
          newState(nextState);
      }
      break;

    // The robot has found the right color, the race can start
    case START :
      // We setup everything for the tag search
      //faut checker la couleur si c'est vert on va dans START
      huskylens.huskylens.writeAlgorithm(ALGORITHM_COLOR_RECOGNITION);
      motor.cmd_robot(0,0);
      if (huskylens.isColor(1)) {
          delay(1700); // Attente du levé de drapeau (ainsi le delay blocant est pratique) 
          huskylens.huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);
          // First the robot look for the tag n°1
          TagNbr = 1;
          newState(TAG);
      }      
      break;
    
    // The robot is looking around if it can find the right tag
    case LOOK_FOR_TAG :
      // on cherche le tag
      if(huskylens.isTag(TagNbr)) {
        motor.cmd_robot(0, 0);
        newState(FOLLOW_TAG);
      }
      else {
        motor.cmd_robot(0, 155);
        if(delayState(50)){ 
          newState(STOP_LOOK);
        } 
      }
      
      
      break;

    case STOP_LOOK : 
      tmp = 1;
      motor.cmd_robot(0, 0);
       if(delayState(300)){
          newState(LOOK_FOR_TAG);
       }
      break;
    
    // Once the right tag is found the robot will go towards it
    case FOLLOW_TAG : 
      // Did the robot found all the tags ? 
      //If no the robot continue to look for the other
      Serial.println(TagNbr);
        tags.followTag(TagNbr, 160, MAX_HEIGHT_ARUCO);
        if(huskylens.getTag(TagNbr).height >= 140){
          
          TagNbr ++;
          if (TagNbr <= MAX_NB_TAG){
            newState(TAG);
          }
          // If yes, the robot go to the state "VICTORY DANCE"
          else{
            newState(VICTORY_DANCE);
          }
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
          if(delayState(2000)){
            newState(STOP_LOOK);
          }
          break;
        case 2:
          motor.cmd_robot(50,200);
          if(delayState(290)){
            newState(STOP_LOOK);
          }
          break;
        case 3:
          motor.cmd_robot(50,200);
          if(delayState(350)){
            newState(STOP_LOOK);
          }
          break;
        case 4:
          motor.cmd_robot(50,200);
          if(delayState(400)){
            newState(STOP_LOOK);
          }
          break;
        case 5:
          motor.cmd_robot(50,-200);
          if(delayState(400)){
            newState(STOP_LOOK);
          }
          break;
        case 6:
          if(tmp == 1){
            motor.cmd_robot(50,-200);
            if(delayState(300)){
              tmp = 2;
              last_millis = millis();
            }
          }
          else if(tmp == 2){
            motor.cmd_robot(255,0);
            if(delayState(1000)){
              newState(STOP_LOOK);
            }
          }
          
          break;
        default:
          newState(STOP_LOOK);
          break;
      }      
      break;

    // The robot found all the tag, the robot stop
    case STOP :
      motor.cmd_robot(0,0);
      break;

    case VICTORY_DANCE:
    Serial.println(stateDance);
      if(stateDance == 1){
        motor.cmd_robot(0,255);
        stateDance++;
        tmp = 500;
        nextState = VICTORY_DANCE;
        newState(IDLE);
      }
      else if(stateDance == 2){
        motor.cmd_robot(0,-255);
        stateDance++;
        tmp = 500;
        nextState = VICTORY_DANCE;
        newState(IDLE);
      }
      else if(stateDance == 3){
        motor.cmd_robot(0,255);
        stateDance=4;
        tmp = 500;
        nextState = VICTORY_DANCE;
        newState(IDLE);
      }
      else if(stateDance == 4){
        motor.cmd_robot(0,-255);
        stateDance++;
        tmp = 500;
        nextState = VICTORY_DANCE;
        newState(IDLE);
      }
      else if(stateDance == 5){
        motor.cmd_robot(-255,0);
        stateDance++;
        tmp = 500;
        nextState = VICTORY_DANCE;
        newState(IDLE);
      }
      else if(stateDance == 6){
        motor.cmd_robot(0,-255);
        stateDance++;
        tmp = 2000;
        nextState = STOP;
        newState(IDLE);
      }
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