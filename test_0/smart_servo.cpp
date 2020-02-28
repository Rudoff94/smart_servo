#include "smart_servo.h"

SmartServo::SmartServo() {
  current_pos = 180;
  target_pos = 180;
  power = 255;
  min_pos = 0;
  max_pos = 359;
  direction = UP_DIR;

}

void SmartServo::init_pid(float kp, float kd, float ki, uint8_t min, uint8_t max) {
  pid.init(kp, kd, ki, min, max);
}

void SmartServo::init_motor(uint8_t e_pin, uint8_t d_pin) {
  motor.attach(e_pin, d_pin);
}

void SmartServo::setMinPos(uint16_t min_p) {
  if (min_p >= 0 &&  min_p < max_pos) {
    min_pos = min_p;
  }
}

void SmartServo::setMaxPos(uint16_t max_p) {
  if (max_p <= 359 &&  max_p > min_pos) {
    max_pos = max_p;
  }
}

uint16_t SmartServo::getCurrentPos() {
  return current_pos;
}

void  SmartServo::setTargetPos(uint16_t t_pos, uint8_t pow) {
  power = pow;
  pid.setMaxVal(power);
  setTargetPos(t_pos);
}

void  SmartServo::setTargetPos(uint16_t t_pos) {
  pid.reset();
  if (t_pos < min_pos) {
    target_pos = min_pos;
  }
  else if (t_pos > max_pos) {
    target_pos = max_pos;
  }
  else {
    target_pos = t_pos;
  }
}

void SmartServo::update() {
  int delta = current_pos - target_pos;
  if (delta > 0) {
    //direction = UP_DIR;
    uint8_t current_power = pid.calculate(delta);
    motor.setSpeed(UP_DIR, current_power);
  }
  else {
    //direction = DOWN_DIR;
    uint8_t current_power = pid.calculate(-1 * delta);
    motor.setSpeed(DOWN_DIR, current_power);
  }
}
void SmartServo::stop(){
  motor.stop();
}

bool SmartServo::getDirection(){
  return direction;  
}

void SmartServo::setDirection(bool dir){
  direction = dir;  
}

void SmartServo::increase() { 
  current_pos++;
  if(current_pos > max_pos){
    current_pos = max_pos;
  }
}
void SmartServo::decrease() {
  current_pos--;
  if(current_pos < min_pos){
    current_pos = min_pos;
  }
}
