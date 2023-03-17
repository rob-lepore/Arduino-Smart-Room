#include "SerialTask.h"

SerialTask::SerialTask(Room* room) {
  this->room = room;
  this->state = WAITING;
};

void SerialTask::init(int period) {
  Task::init(period);
  MsgService.init();
};

void SerialTask::tick() {
  switch (this->state) {
    case WAITING:
      if (MsgService.isMsgAvailable()) this->state = READING;
      break;
    case READING:
      Msg* msg = MsgService.receiveMsg();
      String text = msg->getContent();
      String cmd = text.substring(0, text.indexOf(":"));
      String val = text.substring(text.indexOf(":") + 1, text.length());

      if (cmd == "movement") {
        room->setMovement(val == "1");
      } else if (cmd == "level") {
        room->setLightLevel(val.toDouble());
      } else if (cmd == "state") {
        room->setSystemState(val == "1");
      } else if (cmd == "remote") {
        Control c = val == "1" ? Control::SER : Control::AUTO;
        room->setControl(c);
      } else if (cmd == "setLamp" && room->getControl() == Control::SER) {
        room->setLampState(val == "1");
      } else if (cmd == "setBlinds" && room->getControl() == Control::SER) {
        room->setBlindsHeight(val.toInt());
      }
      delete msg;

      this->state = WAITING;
      break;
  }

  Serial.println(room->isLampOn() ? "Lamp On" : "Lamp Off");  // communicate to server the lamp state
};