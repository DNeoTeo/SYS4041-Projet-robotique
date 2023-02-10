#include <Arduino.h>
#include <HUSKYLENS.h>
#include <motor.h>

//Constante - Variables globales

HUSKYLENS huskylens;
//HUSKYLENS green line >> SDA; blue line >> SCL
bool isColor(int indexColor);
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
      if(isColor(1))
      {
        Serial.println("C'est rouge!");
      }
      if(isColor(2)){
        Serial.println("c'est vert!");
      }    
    delay(200);
}

bool isColor(int indexColor){
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