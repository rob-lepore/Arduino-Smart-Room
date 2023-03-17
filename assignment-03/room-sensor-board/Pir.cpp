#include "Arduino.h"
#include "Pir.h"

Pir::Pir(int pin, int calibrationTime = 10)
{
    this->pin = pin;
    pinMode(pin, INPUT);

    // give the sensor some time to calibrate
    Serial.print("Calibrating sensor");
    for (int i = 0; i < calibrationTime; i++)
    {
        Serial.print(".");
        delay(1000);
    }
    Serial.println();
    Serial.println("PIR SENSOR READY.");
    detectedStatus = false;
}

bool Pir::detect()
{
    int current = digitalRead(pin);
    return current;
}