#ifndef __LED__
#define __LED__

class Light {
private:
    enum {OFF, ON} state;
    int pin;
public:

    Light(int pin);
    void turnOn();
    void turnOff();
    void toggle();
    bool isOn();
};

#endif