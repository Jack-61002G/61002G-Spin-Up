#include "globals.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

void intaketoggle() {
  intake_state = false;

  while (1 == 1) {
    /*if (front_intake.get_torque() >= 1) {
      front_intake.move(0);
      gate.move(0);
    }*/

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      if (!intake_state) {
        front_intake.move(127);
        gate.move(127);
        intake_state = !intake_state;
      } else {
        front_intake.move(0);
        gate.move(0);
        intake_state = !intake_state;
      }
    }

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
        gate.move(-127);
        front_intake.move(127);
      }
    }

    pros::delay(10);
  }