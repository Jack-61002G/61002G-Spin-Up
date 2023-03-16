#include "main.h"
//#include "autons.hpp"
#include "Catapult.hpp"
#include "autons.hpp"
#include "globals.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "autoSelect/selection.h"

  #define fireDelay 350
  #define ASYNC(func) pros::Task task{ [=] {pros::delay(fireDelay); func();} }

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

 void screen() {
    // loop forever
    while (true) {
        lemlib::Pose pose = chassis.getPose(); // get the current position of the robot
        pros::lcd::print(0, "x: %f", pose.x); // print the x position
        pros::lcd::print(1, "y: %f", pose.y); // print the y position
        pros::lcd::print(2, "heading: %f", pose.theta); // print the heading
        pros::delay(10);
    }
}

void initialize() {

  selector::init();

  
  pros::lcd::initialize();
  chassis.calibrate();
  cata.startTask(); // start the catapult task
  pros::Task screenTask(screen); // create a task to print the position to the screen
  

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

void auton() {

  chassis.setPose({53, -31, 90});

  chassis.moveTo(59.5, -31, 1000, 200);
  spinRoller();
  pros::delay(700);
  
  ASYNC(cata.fire);
  chassis.moveTo(53, -31, 1000, 90);
  chassis.turnTo(-52, -52, 500, true);
  

    intakeState = 1;
  intaketoggle();

  chassis.turnTo(35, -12, 1000);
  chassis.moveTo(32, -8, 2000, 200);

  chassis.moveTo(16, 5, 4000, 50);
  pros::delay(500);
  
  chassis.moveTo(23, -10, 1000, 90);
  chassis.turnTo(-56, -44, 1000, true);
  
  cata.fire();
  
  chassis.turnTo(-26, 56, 1000);
  chassis.moveTo(-26, 56, 5000, 70);
  

  chassis.moveTo(-10, 24, 2000, 90);

  chassis.turnTo(-52, -52, 1000, true);
  cata.fire();
  chassis.turnTo(31, 61, 1000);
  chassis.moveTo(31, 61, 3000, 90);
  spinRoller();

}

void autonomous() {
  
  if(selector::auton == 1){auton();};

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
      cata.fire();
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
