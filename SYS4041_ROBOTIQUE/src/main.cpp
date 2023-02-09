#include <Arduino.h>
#include <HUSKYLENS.h>
#include <TCC-motor.h>
#include <TCC-Huskylens.h>


/********** Constante - Variables globales *********/
//HUSKYLENS huskylens; //HUSKYLENS green line >> SDA; blue line >> SCL


/********** Functions *********/
void printResult(HUSKYLENSResult result);
bool isTag(int indexTag);
HUSKYLENSResult getTag(int indexTag);
bool delayState (int delaytime);
void newState(state_e newE);


/********** Setup *********/
void setup() {
    Serial.begin(115200);
    Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
    init_motorAB();
}

/********** Loop *********/
float asservAP = 0.3, asservAI = 0.3, somErrA = 0, somErrL = 0, asservLP = 0.7, asservLI = 0.1;
void loop() {
    stateMachine();
}

void printResult(HUSKYLENSResult result){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else{
        Serial.println("Object unknown!");
    }
}



// bool isTag(int indexTag){
//     if(!huskylens.request()){
//         return false;
//     }
//     while(huskylens.available()){
//         HUSKYLENSResult result = huskylens.read();
//         if(result.ID == indexTag){
//           return true;
//         }
//     }
//     return false;
// } 

HUSKYLENSResult getTag(int indexTag){
    HUSKYLENSResult result;
    if(!huskylens.request()){
        result.ID = -1;
        return result;
    }
    while(huskylens.available()){
        result = huskylens.read();
        if(result.ID == indexTag){
          return result;
        }
    }
    result.ID = -1;
    return result;
} 


/********** State Machine *********/
void stateMachine() {
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
  int TagNbr;

  // Switch case
  switch (state)
  {
    case IDLE :
      //faut checker la couleur si c'est vert on va dans START
      cmd_robot(0,0);
      if (checkcolor()) {
        if(delayState(1000)) {
            newState(START);
        }
      }
      break;

    case START :
      //c'est vert, on démarre et on va dans look for tag
      TagNbr = 1;
      huskylens.writeAlgorithm (ALGORITHM_TAG_RECOGNITION);
      if(delayState(1000)) {
          newState(LOOK_FOR_TAG);
      }
      break;
    
    case LOOK_FOR_TAG :
      // on cherche le tag
      if (isTag(TagNbr)) {
        if(delayState(1000)) {
              newState(TAG);
        }
      }
      break;
    
    case TAG :
      //on incrémente et on revient dans look for tag
      TagNbr ++;
      if (TagNbr <= 5) {
        if(delayState(1000)) {
              newState(LOOK_FOR_TAG);
        }
      }
      else {
        if(delayState(1000)) {
            newState(STOP);
        }
      }
      
      break;

    case STOP :
    // on a trouvé tous les tags donc on s'arrête
      cmd_robot(0,0);
      break;

    default:
        break;
  }
}

void newState (state new) {
    //Serial.println(new);
    state = new;
    last.millis = millis();
}

bool delayState(int delaytime){
    return((millis().last.millis)>= delaytime);
}