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
    bool checkcolor();
    bool isColor(int indexColor);
};




