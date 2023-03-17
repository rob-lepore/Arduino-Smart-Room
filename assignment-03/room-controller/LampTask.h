#ifndef __LTASK__
#define __LTASK__

#include "Room.h"
#include "Task.h"
#define LIGHTTHR 10


class LampTask : public Task {

private:
  Room* room;
  enum {ON, OFF} state;

public:
  LampTask(Room* room);
  void tick();
};

#endif