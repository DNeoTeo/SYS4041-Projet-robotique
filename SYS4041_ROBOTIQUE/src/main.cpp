#include <Arduino.h>
#include <HUSKYLENS.h>
#include <TCC-motor.h>
#include <TCC-Huskylens.h>


/********** Constante - Variables globales *********/
//HUSKYLENS huskylens; //HUSKYLENS green line >> SDA; blue line >> SCL
TCC_Huskylens huskylens;
float asservAP = -0.3, asservAI = 0.1, 
        asservLP = 0.8, asservLI = 0,
        somErrA = 0, somErrL = 0;


/********** Functions *********/
//void printResult(HUSKYLENSResult result);
//bool isTag(int indexTag);
//HUSKYLENSResult getTag(int indexTag);
bool delayState (int delaytime);
void newState(state_e newE);
void followTag(int IDTag, int consigneCentre, int consigneDist);
void followTagAA(int IDTag, int consigneCentre, int consigneDist);


/********** Setup *********/
void setup() {
    Serial.begin(115200);
    huskylens.setup();
    init_motorAB();
}

/********** Loop *********/
float asservAP = 0.3, asservAI = 0.3, somErrA = 0, somErrL = 0, asservLP = 0.7, asservLI = 0.1;
//--------------------------------LOOP
void loop() {
    stateMachine();
    followTag(2, 160, 180);

}

void followTag(int IDTag, int consigneCentre, int consigneDist){// 2 160 190
  HUSKYLENSResult tag = getTag(IDTag);
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
    if(input2 >= 180){
      output2 = output2*(-1);
    }
    
    
    cmd_robot(output2, output);
  }
  else {
    Serial.println("Mauvais tag");
    cmd_robot(0, 0);
  }
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