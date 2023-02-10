/*********** TCC-Huskylens class ***********/

#include "TCC-Huskylens.h"

/********** Constructor **********/
TCC_Huskylens::TCC_Huskylens() {}


/********** Setup and connect the camera **********/
void TCC_Huskylens::setup() {
    Wire.begin();
    while (!huskylens.begin(Wire))
    {
        Serial.println(F("Begin failed!"));
        Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
        Serial.println(F("2.Please recheck the connection."));
        delay(100);
    }
}


/********** Check if the tag found is the right one **********/
bool TCC_Huskylens::isTag(int indexTag){
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

/********** Get the current tag informations **********/
HUSKYLENSResult TCC_Huskylens::getTag(int indexTag){
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


/********** Print the informations about the current tag **********/
void TCC_Huskylens::printResult(){
    if (result.command == COMMAND_RETURN_BLOCK){
        Serial.println(String()+F("Block:xCenter=")+result.xCenter+F(",yCenter=")+result.yCenter+F(",width=")+result.width+F(",height=")+result.height+F(",ID=")+result.ID);
    }
    else if (result.command == COMMAND_RETURN_ARROW){
        Serial.println(String()+F("Arrow:xOrigin=")+result.xOrigin+F(",yOrigin=")+result.yOrigin+F(",xTarget=")+result.xTarget+F(",yTarget=")+result.yTarget+F(",ID=")+result.ID);
    }
    else {
        Serial.println("Object unknown!");
    }
}


/********** Check if the color found is the right one (red) **********/
bool TCC_Huskylens::isColor(int indexColor){
    if(!huskylens.request()){
        return false;
    }
    while(huskylens.available()){
        HUSKYLENSResult result = huskylens.read();
        if(result.ID == indexColor){
          return true;
        }
    }
    return false;
} 