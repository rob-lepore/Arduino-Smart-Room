#include "Arduino.h"
#include "Room.h"
#include "Scheduler.h"
#include "Task.h"
#include "LampTask.h"
#include "BlindsTask.h"
#include "BluetoothTask.h"
#include "SerialTask.h"

#define LED_PIN 8
#define MOTOR_PIN 4

Room* room;

Scheduler* sched;
Task* lampTask;
Task* blindsTask;
Task* btTask;
Task* sTask;


void setup() {
  Serial.begin(9600);
  while (!Serial) {}
  Serial.println("ready to go.");
  delay(500);

  room = new Room(LED_PIN, MOTOR_PIN);

  sched = new Scheduler();
  sched->init(200);

  lampTask = new LampTask(room);
  blindsTask = new BlindsTask(room);
  btTask = new BluetoothTask(room);
  sTask = new SerialTask(room);

  lampTask->init(200);
  blindsTask->init(200);
  btTask->init(200);
  sTask->init(200);

  sched->addTask(lampTask);
  sched->addTask(blindsTask);
  sched->addTask(btTask);
  sched->addTask(sTask);
}

void loop() {
  sched->schedule();
}