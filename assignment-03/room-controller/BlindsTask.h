#ifndef __BTASK__
#define __BTASK__

#include "Room.h"
#include "Task.h"


class BlindsTask : public Task {

private:
  Room* room;
  enum {AUTO, REMOTE} state;

public:
  BlindsTask(Room* room);

  void tick();
};

#endif