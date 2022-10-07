#include "globals.hpp"
#include "main.h"

void flywheelpid() {
  int target{50}; // our voltage target
  double gain{100};
  double error{0};
  int output{0};

  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      if (flywheel_state == false) {
        target = 170;
        flywheel_state = !flywheel_state;
      } else {
        target = 50;
        flywheel_state = !flywheel_state;
      }
    }

    error = target - spinnyman.getActualVelocity(); 

    output = (error * gain) + 7500;

    if (output >= 12000){
      output = 12000;
    }

    spinnyman.moveVoltage(output);

    pros::delay(10);
  }
}