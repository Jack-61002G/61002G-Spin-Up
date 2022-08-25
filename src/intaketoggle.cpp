#include "globals.h"
#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"


void intaketoggle() {

  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      if (intake_state) {
        front_intake.move(127);
        intake_state = !intake_state;
      } else {
        front_intake.move(0);
        intake_state = !intake_state;
      }
    }
    pros::delay(10);
  }
}

void gatetoggle() {

  while (true) {
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      if (gate_state) {
        gate.move(127);
        gate_state = !gate_state;
      } else {
        gate.move(0);
        gate_state = !gate_state;
      }
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP) and
               (master.get_digital_new_press(
                   pros::E_CONTROLLER_DIGITAL_LEFT))) {
      gate.move_absolute(720, 100);
    }
    pros::delay(10);
  }
}