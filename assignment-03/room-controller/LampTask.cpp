#include "LampTask.h"

LampTask::LampTask(Room* room) {
  this->room = room;
  this->state = OFF;
};

void LampTask::tick() {

  switch (this->state) {
    case ON:
      room->turnLampOn();

      if (!room->isLampOn() && room->getControl() != Control::AUTO)
        this->state = OFF;
      if (!room->movementDetected() && room->getControl() == Control::AUTO)
        this->state = OFF;
      if (room->getLightLevel() > LIGHTTHR && room->getControl() == Control::AUTO) {
        this->state = OFF;
      }

      break;
    case OFF:
      room->turnLampOff();

      if (room->movementDetected() && room->getLightLevel() < LIGHTTHR && room->getControl() == Control::AUTO)
        this->state = ON;
      if (room->isLampOn() && room->getControl() != Control::AUTO)
        this->state = ON;

      break;
  }

};