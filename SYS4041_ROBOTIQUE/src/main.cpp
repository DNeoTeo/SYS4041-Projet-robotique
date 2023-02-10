#include <Arduino.h>
//#include <HUSKYLENS.h>
#include "TCC-motor.h"
#include "TCC-Huskylens.h"
#include "TCC-Tag.h"


/********** Constante - Variables globales *********/
//HUSKYLENS huskylens; //HUSKYLENS green line >> SDA; blue line >> SCL
TCC_Huskylens huskylens;
TCC_Motor motor;
TCC_Tag tag(huskylens, motor);

#define MAX_HEIGHT_ARUCO 170
#define MAX_NB_TAG 7
// Variables
  enum state_e {
    IDLE,
    START,
    LOOK_FOR_TAG,
    STOP_LOOK,
    FOLLOW_TAG,
    TAG,
    STOP
  };

  state_e state = IDLE;
  long last_millis;
  int TagNbr = 0;

/********** Functions *********/
bool delayState (int delaytime);
void newState(state_e newE);

float asservAP = -0.3, asservAI = 0.1;
float asservLP = 0.9, asservLI = 0;
float somErrA = 0, somErrL = 0;
void followTag(int IDTag, int consigneCentre, int consigneDist){// 2 160 190
  
  HUSKYLENSResult tag = huskylens.getTag(IDTag);
  Serial.println(tag.ID);
  if(tag.ID != -1){
    int input = tag.xCenter;
    int erreur = consigneCentre - input;
    int output = (int)((float)(erreur * asservAP));
    output = max(output, (-255));
    output = min(output, 255);

    int input2 = tag.height;
    int erreur2 = consigneDist - input2;
    int output2 = (int)((float)(erreur2 * asservLP));
  
    output2 = max(output2, -255);
    output2 = min(output2, 255);
    /*if(input2 >= consigneDist){
      output2 = output2*(-1);
    }*/
    
    motor.cmd_robot(output2, output);
  }
  else {
    motor.cmd_robot(0, 0);
  }
}

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
}


/********** State Machine *********/
void stateMachine() {
  // Switch case
  switch (state)
  {
    case IDLE :
      //faut checker la couleur si c'est vert on va dans START
      motor.cmd_robot(0,0);
      if (true) { //huskylens.isColor(1)
        newState(START);
      }
      break;

    case START :
      //c'est vert, on démarre et on va dans look for tag
      TagNbr = 1;
      
      huskylens.huskylens.writeAlgorithm(ALGORITHM_TAG_RECOGNITION);
      if(delayState(1000)) {
        newState(TAG);
      }
      break;
    
    case LOOK_FOR_TAG :
      // on cherche le tag //PETIT ACOU
      if(huskylens.isTag(TagNbr)) {
        motor.cmd_robot(0, 0);
        newState(FOLLOW_TAG);
      }
      else {
        motor.cmd_robot(0, 155);
        if(delayState(50)){ //A FAIRE
          newState(STOP_LOOK);
        } 
      }
      
      
      break;

    case STOP_LOOK : 
      motor.cmd_robot(0, 0);
       if(delayState(300)){
          newState(LOOK_FOR_TAG);
       }
      break;
    
    case FOLLOW_TAG : 
      if (TagNbr <= MAX_NB_TAG){
        //tag.followTag(TagNbr, 160, MAX_HEIGHT_ARUCO+30);
        followTag(TagNbr, 160, MAX_HEIGHT_ARUCO+30);
        int heightTAG = huskylens.getTag(TagNbr).height;
        Serial.print("HEIGHT= ");
        Serial.println(heightTAG);
        if(heightTAG >= 140){
          TagNbr ++;
          newState(TAG);
        }
      }
      else{
        newState(STOP);
      }
    break;

    case TAG :
      //on incrémente et on revient dans look for tag
      //Serial.print("Tag nb= ");
      //Serial.println(TagNbr);
       switch (TagNbr)
      {
        case 1:
          motor.cmd_robot(255,0);
          if(delayState(1700)){
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
          if(delayState(400)){
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
          motor.cmd_robot(50,-200);
          if(delayState(300)){
            newState(STOP_LOOK);
          }
          break;
        case 7:
        motor.cmd_robot(0,-200);
        if(delayState(300)){
          motor.cmd_robot(0,200);
          if(delayState(600)){
            motor.cmd_robot(0,-200);
            if(delayState(900)){
              motor.cmd_robot(0,-200);
              if(delayState(1200)){
                newState(STOP);
              }
            }
          }
        }
        default:
          newState(STOP);
          break;
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
