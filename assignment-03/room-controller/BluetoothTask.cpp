#include "BluetoothTask.h"

BluetoothTask::BluetoothTask(Room* room) {
  this->room = room;
  this->channel = new SoftwareSerial(RX_PIN, TX_PIN);
  this->channel->begin(9600);
  this->state = WAITING;
}

void BluetoothTask::tick() {

  switch (this->state) {
    case WAITING:
      if(channel->available()) this->state = READING;
      break;
    case READING:
      String msg = channel->readString();
      if (msg == "on\n" && room->getControl() == Control::BT) {
        room->setLampState(true);
      } else if (msg == "off\n" && room->getControl() == Control::BT) {
        room->setLampState(false);
      } else if (msg == "remote on\n") {
        room->setControl(Control::BT);
      } else if (msg == "remote off\n") {
        room->setControl(Control::AUTO);
      } else if (room->getControl() == Control::BT) {
        room->setBlindsHeight(msg.toInt());
      }
      this->state = WAITING;
      break;
  }

}