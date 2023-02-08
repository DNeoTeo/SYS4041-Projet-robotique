#include <Arduino.h>
#include <HUSKYLENS.h>
#include <motor.h>

//Constante - Variables globales

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
bool isTag(int indexTag);
void printResult(HUSKYLENSResult result);

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
}

void loop() {
    Serial.println(F("###########"));
      if(isTag(7))
      {
        Serial.println("Bravo ya un escalier");
      }
      if(isTag(8)){
        Serial.println("Pas content, il est ou l'escalier");
      }    
    delay(200);
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