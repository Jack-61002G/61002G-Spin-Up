#include "globals.hpp"
#include "main.h"

void flywheelpid() {
  // define variables we need for the tbh controller
  int target{4000}; // our voltage target
  double gain{1};
  double error{0};
  int output{0};
  double tbh{0};
  double prev_error{0};

  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      if (flywheel_state == false) {
        target = 7500;
        flywheel_state = !flywheel_state;
      } else {
        target = 4000;
        flywheel_state = !flywheel_state;
      }
    }

    if (spinnyman.getActualVelocity() <= 140) {
    spinnyman.moveVoltage(target);
    }else {
    spinnyman.moveVoltage(3500);
    }


    spinnyman.moveVoltage(target);
    pros::delay(10);
  }
}