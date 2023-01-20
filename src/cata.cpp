#include "globals.h"
#include "main.h"


  bool fired{false};

  int getState() { // returns true if catapult is in loaded position

    if ((limitButton.get_value() == false)) {
      return false;

    } else {
      return true;
    }
  }

  void reload() { // loads catapult

    if (getState() == false) {
      catapultMotor = 127;
    } else {
      catapultMotor = 0;
      fired = false;
    }
  }

  void driverCata() {

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
      catapultMotor = 127;
    } else {
      reload();
    }

  }

  void autonCata() {

    catapultMotor = 127;
    pros::delay(250);
    while (getState() == false) {
      pros::delay(10);
    }
    catapultMotor.move_voltage(0);

  }