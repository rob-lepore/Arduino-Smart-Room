#include "Photoresistor.h"
#include "Arduino.h"

Photoresistor::Photoresistor(int pin)
{
    this->pin = pin;
    pinMode(pin, INPUT);
}

double Photoresistor::getLightLevel()
{
    int value = analogRead(pin);
    double valueInVolt = ((double)value) * 5 / 1024;
    //Serial.println(String(value) + " -> in volt: " + valueInVolt);
    return valueInVolt;
}