#include <Arduino.h>
#include <HUSKYLENS.h>
#include <TCC-motor.h>
//#include <TCC-Huskylens.h>


//--------------------------------Constante - Variables globales

float asservAP = -0.3, asservAI = 0.1, 
        asservLP = 0.8, asservLI = 0,
        somErrA = 0, somErrL = 0;

HUSKYLENS huskylens; //HUSKYLENS green line >> SDA; blue line >> SCL
enum state_e {
    IDLE,
    STOP,
    LEFT,
    RIGHT,
    FORWARD
};

state_e state = IDLE;
long last_millis;

//--------------------------------HEADER
void printResult(HUSKYLENSResult result);
bool isTag(int indexTag);
HUSKYLENSResult getTag(int indexTag);
bool delayState (int delaytime);
void newState(state_e newE);
void followTag(int IDTag, int consigneCentre, int consigneDist);
void followTagAA(int IDTag, int consigneCentre, int consigneDist);

//--------------------------------SETUP
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
//--------------------------------LOOP
void loop() {
  followTag(2, 160, 180);
  /*switch (state)
  {
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
  }*/





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

void newState(state_e newE) {
    state = newE;
    last_millis = millis();
}

bool delayState (int delaytime) {
    return ((millis()-last_millis)>=delaytime);
}

bool isTag(int indexTag){
    if(!huskylens.request()){
        return false;
    }
    while(huskylens.available()){
        HUSKYLENSResult result = huskylens.read();
        if(result.ID == indexTag){
          return true;
        }
    }
    return false;
} 

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
