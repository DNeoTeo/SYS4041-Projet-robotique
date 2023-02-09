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




void followTagAA(int IDTag, int consigneCentre, int consigneDist){
  HUSKYLENSResult tag = getTag(2);
  if(tag.ID != -1){
    int input = tag.xCenter;
    int erreur = consigneCentre - input;
    int output = (int)((float)(erreur * asservAP)) + (int)(float)(somErrA * asservAI);
    output = max(output, (-255));
    output = min(output, 255);
    if(input == 160)
      somErrA = 0;
    else 
      somErrA += erreur*asservAI;

    int input2 = tag.height;
    int erreur2 = consigneDist - input2;
    int output2 = (int)((float)(erreur2 * asservLP)); //+ (int)(float)(somErrL * asservLI);
    output2 = max(output2, -255);
    output2 = min(output2, 255);
    /*if(input2 >= 180){
      somErrL = 0;
      output2 *= (-1);
    }
    else {
      somErrL += erreur2*asservLI;
    }*/
    cmd_robot(output2, output);
  }
  else {
    //Serial.println("Mauvais tag");
    cmd_robot(0, 0);
  }
}


void followTag(int IDTag, int consigneCentre, int consigneDist){
  float asservAP = -0.3, asservAI = 0, 
        asservLP = 0.8, asservLI = 0,
        somErrA = 0, somErrL = 0;
  HUSKYLENSResult tag = getTag(2);
  if(tag.ID != -1){
    int consigneCentre = 160;
    int input = tag.xCenter;
    int erreur = consigneCentre - input;
    int output = (int)((float)(erreur * asservAP)) + (int)(float)(somErrA * asservAI);
    output = max(output, (-255));
    output = min(output, 255);
    if(input == 160)
      somErrA = 0;
    else 
      somErrA += erreur*asservAI;

    int input2 = tag.height;
    int consigneDist = 180;
    int erreur2 = consigneDist - input2;
    int output2 = (int)((float)(erreur2 * asservLP)) + (int)(float)(somErrL * asservLI);
    //Serial.println(output2);Serial.println(" / ");Serial.println(output);
    
    output2 = max(output2, -255);
    output2 = min(output2, 255);
    if(input2 >= 180){
      somErrL = 0;
      output2 *= (-1);
    }
    else {
      somErrL += erreur2*asservLI;
    }
    
    cmd_robot(output2, output);
  }
  else {
    Serial.println("Mauvais tag");
    cmd_robot(0, 0);
  }
}

