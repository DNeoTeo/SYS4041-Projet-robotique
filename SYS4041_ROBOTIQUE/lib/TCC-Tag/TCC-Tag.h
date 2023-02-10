/********** TCC-Tag class **********/

/* This class regroup all the function linked with the search
 * for a tag and it's optimisation.
 * These function are combining functions from TCC-Motor and TCC-Huskylens.
 * All the function directly linked with the use of the lens are in the librairy TCC-Huskylens.
 */

#ifndef TAG_H
#define TAG_H

#include "TCC-Motor.h"
#include "TCC-Huskylens.h"



class TCC_Tag {
    private:
        TCC_Huskylens huskylens;
        TCC_Motor motor;

        float asservAP = -0.3, asservAI = 0.1;
        float asservLP = 0.8, asservLI = 0;
        float somErrA = 0, somErrL = 0;

    public:
        TCC_Tag();
        void setup(TCC_Huskylens _huskylens, TCC_Motor _motor);
        void followTag(int IDTag, int consigneCentre, int consigneDist);

};
#endif