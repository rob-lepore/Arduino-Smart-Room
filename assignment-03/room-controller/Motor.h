#ifndef __MOTOR__
#define __MOTOR__
#include "ServoTimer2.h"

class Motor {
private:
  int pin; 
  ServoTimer2 motor; 

public:
  Motor(int pin);

  void on();
  void setPosition(int angle);
  int getPosition();
  void off();
};

#endif