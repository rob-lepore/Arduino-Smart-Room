#ifndef __PIR__
#define __PIR__

class Pir
{
private:
    bool detectedStatus;
    int pin;

public:
    Pir(int pin, int calibrationTime);
    bool detect();
};

#endif