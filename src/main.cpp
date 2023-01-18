#include "main.h"
#include "ARMS/chassis.h"
#include "cata.h"
#include "globals.h"
#include "ARMS/config.h"

/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  arms::init();
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

void autonomous() {

  arms::chassis::move({12, 12, 90}, 85);
  // move back to 0,0,0
  arms::chassis::move({0, 0, 0}, 85);

}

void opcontrol() {

  Catapult cata;

  int power = 0;
  int turn = 0;

  pros::ADIDigitalOut piston('B');
  piston.set_value(false);

  while (true) {

    power = 0.787 * master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    turn = 0.787 * master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

    arms::chassis::arcade(power, turn);

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      if (intakeState == 0) {
        intakeState = -1;
        intaketoggle();
      } else {
        intakeState = 0;
        intaketoggle();
      }
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      if (intakeState == 0) {
        intakeState = 1;
        intaketoggle();
      } else {
        intakeState = 0;
        intaketoggle();
      }
    }

    if (cata.doCata()) {
      catapultMotor.move_voltage(12000);
    } else {
      catapultMotor.move_voltage(0);
    }

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) &&
        master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      piston.set_value(true);
    }

    pros::delay(20);
  }
}
