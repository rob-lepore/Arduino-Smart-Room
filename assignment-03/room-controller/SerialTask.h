#ifndef __SERIALTASK__
#define __SERIALTASK__

#include "Task.h"
#include "Room.h"
#include "MsgService.h"

class SerialTask : public Task {

private:
  Room* room;
  enum {WAITING, READING} state;

public:
  SerialTask(Room* room);

  void init(int period);

  void tick();
};




#endif