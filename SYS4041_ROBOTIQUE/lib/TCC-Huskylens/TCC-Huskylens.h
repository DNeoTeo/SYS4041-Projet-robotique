/********** TCC-Huskylens class **********/
/* This class regroup all the useful functions from the HUSKYLENS official librairy.
 * New functions were created for optimisation purposes.
 */

#ifndef HUSKY_H
#define HUSKY_H

#include <HUSKYLENS.h>

class TCC_Huskylens {
    private:
        HUSKYLENSResult result;

    public:
        HUSKYLENS huskylens;

        TCC_Huskylens();
        void setup();
        bool isTag(int indexTag);
        HUSKYLENSResult getTag(int indexTag);
        void printResult();
        bool isColor(int indexColor);
};
#endif


