#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int pin){
  this->pin = pin;  
} 

void Motor::on(){
  motor.attach(pin);    
}

void Motor::setPosition(int angle){
  // 750 -> 0, 2250 -> 180 
  // 750 + angle*(2250-750)/180
  float coeff = (2250.0-750.0)/180;
  motor.write(750 + angle*coeff);              
}

int Motor::getPosition() {
  float coeff = (2250.0-750.0)/180;
  return (motor.read()-750)/coeff;
}

void Motor::off(){
  motor.detach();    
}