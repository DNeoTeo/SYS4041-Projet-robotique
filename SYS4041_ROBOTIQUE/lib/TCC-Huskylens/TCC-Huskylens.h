#include <HUSKYLENS.h>

class TCC_Huskylens {
private:
    HUSKYLENS huskylens;
    HUSKYLENSResult result;

public:
    TCC_Huskylens();
    void setup();
    bool isTag(int indexTag);
    HUSKYLENSResult getTag(int indexTag);
    void printResult();
};



