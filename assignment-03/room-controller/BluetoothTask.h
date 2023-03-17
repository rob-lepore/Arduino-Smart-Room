#ifndef __BTTASK__
#define __BTTASK__

#include "Room.h"
#include "SoftwareSerial.h"
#include <Wire.h>
#include "Task.h"

#define RX_PIN 2
#define TX_PIN 3
class BluetoothTask : public Task {

private:
  Room* room;
  SoftwareSerial* channel;

  enum {WAITING, READING} state;

public:
  BluetoothTask(Room* room);

  void tick();
};

#endif