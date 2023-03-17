#include "BlindsTask.h"

BlindsTask::BlindsTask(Room* room) {
  this->room = room;
  this->state = AUTO;
};

void BlindsTask::tick() {

  switch (this->state) {
    case AUTO:
      if (room->getControl() == Control::AUTO) {

        if (room->isSystemOn() && room->movementDetected() && !room->firstAccessHappened()) {
          room->moveBlinds(0);
          room->setFirstAccess(true);
        }

        if (!room->isSystemOn() && !room->movementDetected() && room->getBlindsHeight() != 180) {
          room->moveBlinds(180);
          room->setFirstAccess(false);
        }

      } else {
        this->state = REMOTE;
      }

      break;
    case REMOTE:

      if (room->getControl() == Control::AUTO) {
        this->state = AUTO;
      } else {
        room->moveBlinds(room->getBlindsHeight());
      }

      break;
  }
}