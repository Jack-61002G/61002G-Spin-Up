#include "main.h"
#include "pros/misc.h"
#include "ryanlib/api.hpp"
using namespace okapi;

void initialize() {}

void disabled() {} 

void competition_initialize() {}

void autonomous() {}

void opcontrol() {

  pros::Task catapult (cataTask);
  auto model = chassis->getModel();
  
  while (true) {

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      if (intakeState == 0) {
        intakeState = -1;
        intaketoggle();
      } else {intakeState = 0; intaketoggle();}
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (intakeState == 0) {
        intakeState = 1;
        intaketoggle();
      } else {intakeState = 0; intaketoggle();}
    }

    model->curvature(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
                     master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 0.05);
    pros::delay(10);
  }
}
