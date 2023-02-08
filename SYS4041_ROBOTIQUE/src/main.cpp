#include <Arduino.h>
#include <HUSKYLENS.h>
#include <motor.h>

//Constante - Variables globales

#define pinMotorDir_A 2
#define pinMotorPWM_A 3
#define pinMotorDir_B 8
#define pinMotorPWM_B 9

HUSKYLENS huskylens; //HUSKYLENS green line >> SDA; blue line >> SCL

bool isTag(int indexTag);
void printResult(HUSKYLENSResult result);



void setup() {
  Serial.begin(115200);
/*
  Wire.begin();
  while (!huskylens.begin(Wire))
  {
      Serial.println(F("Begin failed!"));
      Serial.println(F("1.Please recheck the \"Protocol Type\" in HUSKYLENS (General Settings>>Protocol Type>>I2C)"));
      Serial.println(F("2.Please recheck the connection."));
      delay(100);
  }*/
  pinMode(pinMotorDir_A, OUTPUT);
  pinMode(pinMotorPWM_A, OUTPUT);
  pinMode(pinMotorDir_B, OUTPUT);
  pinMode(pinMotorPWM_B, OUTPUT);
    
}

void loop() {
  /*Serial.println(F("###########"));
    if(isTag(7))
    {
      Serial.println("Bravo ya un escalier");
    }
    if(isTag(8)){
      Serial.println("Pas content, il est ou l'escalier");
    }    
  delay(200);*/

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




