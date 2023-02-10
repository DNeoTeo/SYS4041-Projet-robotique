#include "TCC-Tag.h"


TCC_Tag::TCC_Tag(TCC_Huskylens _huskylens, TCC_Motor _motor) {
  huskylens = _huskylens;
  motor = _motor;
}

/********** Asservissement poursuite de Tag *********/
void TCC_Tag::followTag(int IDTag, int consigneCentre, int consigneDist){// 2 160 190
  
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