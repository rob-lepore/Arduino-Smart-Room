#include "Arduino.h"

#ifndef __TASK__
#define __TASK__

class Task
{

protected:
    int period;
    int timeElapsed;

public:
    virtual void init(int period){
        this->period = period;
        this->timeElapsed = 0;
    };
    virtual void tick() = 0;

    void setPeriod(int period){
        this->period = period;
    }

    bool updateAndCheckTime(int basePeriod)
    {
        timeElapsed += basePeriod;
        if (timeElapsed >= period)
        {
            timeElapsed = 0;
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif