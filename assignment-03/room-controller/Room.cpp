#include "Room.h"

Room::Room(int lampPin, int motorPin) {
  this->lamp = new Light(lampPin);
  this->motor = new Motor(motorPin);
  this->motor->on();

  this->movement = false;
  this->systemOn = false;
  this->lightLevel = 0.0;
  this->turnLampOff();
  this->setBlindsHeight(180);
  this->firstAccess = false;
  this->control = Control::AUTO;
}

void Room::turnLampOn() {
  this->lampState = true;
  this->lamp->turnOn();
}

void Room::turnLampOff() {
  this->lampState = false;
  this->lamp->turnOff();
}

void Room::setLampState(bool on) {
  this->lampState = on;
}

bool Room::isLampOn() {
  return this->lampState;
}

void Room::setBlindsHeight(int value) {
  this->blindsHeight = value;
}

void Room::moveBlinds(int value) {
  this->blindsHeight = value;
  this->motor->setPosition(value);
}

int Room::getBlindsHeight() {
  return this->blindsHeight;
}

bool Room::isSystemOn() {
  return this->systemOn;
}

bool Room::movementDetected() {
  return this->movement;
}


double Room::getLightLevel() {
  return this->lightLevel;
}

void Room::setControl(Control c) {
  this->control = c;
}

Control Room::getControl() {
  return  this->control;
}

/* 
void Room::setBTControl(bool state) {
  btControl = state;
}

bool Room::isBTControlOn() {
  return btControl;
}

void Room::setSerialControl(bool state) {  
  serialControl = state;
}

bool Room::isSerialControlOn() {
  return serialControl;
} */

void Room::setSystemState(bool state) {
  systemOn = state;
}
void Room::setMovement(bool detected) {
  movement = detected;
}
void Room::setLightLevel(double value) {
  lightLevel = value;
}


bool Room::firstAccessHappened() {
  return this->firstAccess;
}

void Room::setFirstAccess(bool happened){
  this->firstAccess = happened;
}
