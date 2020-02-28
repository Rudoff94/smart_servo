#include "smart_servo.h"


//define photoresistors's ports
#define PHR1 A5
#define PHR2 A6
#define THRESHOLD 400
uint16_t last_val_p1;
uint16_t last_val_p2;

//#define NUM_PHR 2
//uint16_t last_val_p[NUM_PHR];
//uint8_t phr_pins[NUM_PHR] = {A5, A6};
String input;
SmartServo srv;
long t;

void setup() {
  Serial.begin(9600);
  srv.init_pid(1.0, 2.0, 0.0, 0.0, 255.0);
  srv.init_motor(3, 4);
}

void loop() {
  if (Serial.available()) {
    input = Serial.readStringUntil(" ");
    if (input != "") {
      Serial.println(input.toInt());
      srv.stop();
      srv.setTargetPos(input.toInt());
    }
  }

  //  for (int i = 0; i < NUM_PHR; i++) {
  //    uint16_t phr_val = analogRead(phr_pins[i]);
  //    if (phr_val > THRESHOLD && last_val_p[i] < THRESHOLD) {
  //      if (srv.getDirection()) {
  //        srv.increase();
  //      }
  //      else {
  //        srv.decrease();
  //      }
  //    }
  //
  //    last_val_p[i] = phr_val;
  //  }

  phr1_val = analogRead(PHR1);
  phr2_val = analogRead(PHR2);
  if (phr1_val > THRESHOLD && last_val_p1 < THRESHOLD) {
    if (phr2_val < THRESHOLD) {
      srv.increase();
    }
    else {
      srv.decrease();
    }
    last_val_p1 = phr1_val;
  }

  if (phr2_val > THRESHOLD && last_val_p2 < THRESHOLD) {
    if (phr1_val > THRESHOLD) {
      srv.increase();
    }
    else {
      srv.decrease();
    }
    last_val_p1 = phr1_val;
  }
    srv.update();
  }
