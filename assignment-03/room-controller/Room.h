#ifndef __ROOM__
#define __ROOM__

#include <Arduino.h>
#include "Motor.h"
#include "Light.h"

typedef enum { AUTO,
               BT,
               SER } Control;

class Room {

public:

  Room(int lampPin, int motorPin);

  // Communication with ESP
  bool movementDetected();
  double getLightLevel();
  void setSystemState(bool state);
  void setMovement(bool detected);
  void setLightLevel(double value);

  bool isSystemOn();
  bool firstAccessHappened();
  void setFirstAccess(bool happened);

  // Actuators controls
  void turnLampOn();  // called by LampTask
  void turnLampOff();
  void setLampState(bool on);  // called by communication tasks
  bool isLampOn();

  void moveBlinds(int value); // called by BlindsTask
  void setBlindsHeight(int value);  // called by communication tasks
  int getBlindsHeight();

  // Control state
  void setControl(Control c);
  Control getControl();

private:
  Control control;

  bool movement;
  bool systemOn;
  double lightLevel;
  bool firstAccess;

  int blindsHeight;
  bool lampState;
  Light* lamp;
  Motor* motor;
};

#endif