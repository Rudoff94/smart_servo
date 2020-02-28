#include "smart_servo.h"


//define photoresistors's ports
#define PHR1 A5
#define PHR2 A6
#define PHR3 A7
#define THRESHOLD 400
//define indices
#define PHR1_ID 1
#define PHR2_ID 2
#define PHR3_ID 3

uint16_t last_val_p1;
uint16_t last_val_p2;
uint16_t last_val_p3;
uint8_t last_high_index = 0;

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
      uint16_t new_target = input.toInt();
      Serial.println(new_target);
      srv.stop();
      srv.setTargetPos(new_target);
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

  uint16_t phr1_val = analogRead(PHR1);
  uint16_t phr2_val = analogRead(PHR2);
  uint16_t phr3_val = analogRead(PHR3);
  if (phr1_val > THRESHOLD && last_val_p1 < THRESHOLD) {
    if (last_high_index == PHR3_ID) {
      srv.increase();
    }
    else {
      srv.decrease();
    }
    last_val_p1 = phr1_val;
    last_high_index = PHR1_ID;
  }

  if (phr2_val > THRESHOLD && last_val_p2 < THRESHOLD) {
    if (last_high_index == PHR1_ID) {
      srv.increase();
    }
    else {
      srv.decrease();
    }
    last_val_p2 = phr2_val;
    last_high_index = PHR2_ID;
  }

  if (phr3_val > THRESHOLD && last_val_p3 < THRESHOLD) {
    if (last_high_index == PHR2_ID) {
      srv.increase();
    }
    else {
      srv.decrease();
    }
    last_val_p3 = phr3_val;
    last_high_index = PHR3_ID;
  }
  srv.update();
}
