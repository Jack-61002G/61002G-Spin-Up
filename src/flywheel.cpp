#include "globals.h"
#include "main.h"

void flywheelpid() {
  int target = 0;
  double Kp = 1;
  int error = 0;
  int voltage = 0;

  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      if (flywheel_state == false) {
        target = 10000;
        flywheel_state = !flywheel_state;
      } else {
        target = 4000;
        flywheel_state = !flywheel_state;
      }
    }
    error = (target) - (int(spinnyman.getVoltage()));

    voltage += Kp * error;

    spinnyman.moveVoltage(target);
    pros::delay(10);
  }
}