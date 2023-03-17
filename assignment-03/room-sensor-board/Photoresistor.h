#ifndef __LS__
#define __LS__

class Photoresistor
{
private:
    int pin;

public:
    Photoresistor(int pin);
    double getLightLevel();
};

#endif