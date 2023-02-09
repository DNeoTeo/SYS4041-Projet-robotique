#include <Arduino.h>
#include <HUSKYLENS.h>
#include <TCC-motor.h>
//#include <TCC-Huskylens.h>


//Constante - Variables globales

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
void printResult(HUSKYLENSResult result);

bool isTag(int indexTag);
HUSKYLENSResult getTag(int indexTag);
int posTag(int indexTag);

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

void loop() {
    /*for(int i=0; i<256; i+=10){
      for(int j=0; j<256; j+=100)
        cmd_robot(i,j);
    }*/
    /*for (int i=0; i<256; i+=10){
        cmd_robot(i, i);
        //Serial.println(i);
        delay(200);
    }
    
    for (int i=0; i>-256; i-=10){
        cmd_robot(i, i);
        delay(200);
    }*/

    HUSKYLENSResult tag = getTag(8);
    float asservAP = -0.3, asservAI = -0.2, somErrA = 0, somErrL = 0, asservLI = 1.9, asservLP = 0.3;
    if(tag.ID != -1){
      //printResult(tag);
      int consigne = 160;
      int input = tag.xCenter;
      int erreur = consigne - input;
      int output = (int)((float)(erreur * asservAP)) + (int)(float)(somErrA * asservAI);
      output = max(output, (-255));
      output = min(output, 255);
      if(input == 160)
        somErrA = 0;
      else 
        somErrA += erreur;
      input = tag.height;
      consigne = 180;
      erreur = consigne - input;
      int output2 = (int)((float)(erreur * asservLP)) + (int)(float)(somErrL * asservLI);
      output2 = max(output2, -255);
      output2 = min(output2, 255);
      if(input >= 180)
        somErrL = 0;
      else 
        somErrL += erreur;
      cmd_robot(output2, output);
      if(tag.height >= 180)
        cmd_robot(0,0);
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

int posTag(int indexTag){
  
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
