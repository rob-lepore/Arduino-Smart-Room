#include "Light.h"
#include "Arduino.h"

Light::Light(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Light::turnOn() {
    state=ON;
    digitalWrite(pin, HIGH);
}

void Light::turnOff() {
    state=OFF;
    digitalWrite(pin, LOW);
}

void Light::toggle() {
    state = state == ON ? OFF : ON;
    digitalWrite(pin, state);
}

bool Light::isOn() {
    return state == ON;
}
