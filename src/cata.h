#include "globals.h"
#include "pros/motors.hpp"

class Catapult {

  bool cataState = false;
  pros::Motor cata();

public:
  int doCata() { // true - turn motor    false - stop motor

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
      cataState = false;
      return true;

    } else if ((limitButton.get_value() == false) && (cataState == false)) {
      // move catapult down until its reached loading position
      return true;

    } else {
      cataState = true;
      return false;
    }
  }

  void moveCata(bool button) {

    if (button) {

      catapultMotor.move(127);

    } else {
      catapultMotor.move(0);
    }

    if (catapultMotor.get_current_draw() <= 6) {

      catapultMotor.move(127);
    } else {
    }
  }
};