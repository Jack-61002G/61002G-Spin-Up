#include "main.h"
#include "autons.hpp"
#include "globals.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

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

  pros::Task cata_task(cata_task_fn);
  chassis.calibrate();

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
  chassis.setPose({60, -31, 90});

  chassis.moveTo(0, 0, 7000);
  chassis.turnTo(-53, -53, 1000);
}

void opcontrol() {


  pros::ADIDigitalOut piston('B');
  piston.set_value(false);

  int power{0};
  int turn{0};

  while (true) {

    //arcade drive with joystick curve
    power = joystickCurve(master.get_analog(ANALOG_LEFT_Y), false);
    turn = joystickCurve(master.get_analog(ANALOG_RIGHT_X), true);

    left_side_motors.move(power + turn);
    right_side_motors.move(power - turn);


    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      fire();
    }

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

    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) &&
        master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      piston.set_value(true);
    }

    pros::delay(10);
  }
}
