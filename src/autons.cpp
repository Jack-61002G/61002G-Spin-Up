#include "autons.hpp"
#include "EZ-Template/util.hpp"
#include "globals.h"
#include "main.h"
#include "pros/adi.h"
#include "pros/rtos.hpp"

// #include "intake.cpp"

///
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
///

const int DRIVE_SPEED =
    110; // This is 110/127 (around 87% of max speed).  We don't suggest making
        // this 127. If this is 127 and the robot tries to heading correct, it's
        // only correcting by making one side slower.  When this is 87%, it's
        // correcting by making one side faster and one side slower, giving
        // better heading correction.
const int TURN_SPEED = 110;
const int SWING_SPEED = 100;

// It's best practice to tune constants when the robot is empty and with heavier
// game objects, or with lifts up vs down. If the objects are light or the cog
// doesn't change much, then there isn't a concern here.

void garage_constants() {
  chassis.set_slew_min_power(70, 70);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 12, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, .45, 0, 4, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, .45, 0, 4, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 47, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 50, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 35, 1, 150, 3, 250, 500);
  chassis.set_exit_condition(chassis.swing_exit, 50, 2, 250, 5, 250, 500);
  chassis.set_exit_condition(chassis.drive_exit, 35, 30, 150, 150, 250, 500);
}

void modified_exit_condition() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
}

// Drive Examples

void turn_test() { chassis.set_turn_pid(90, TURN_SPEED); }

void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a
  // slew at the start of drive motions for slew, only enable it when the drive
  // distance is greater then the slew distance + a few inches

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED, true);
  chassis.wait_drive();
}

// Auton Functions
void left8Disc() {


  useAltLimitSwitch = true;

  //move into roller and spin it
  chassis.set_drive_pid(7.25, DRIVE_SPEED);
  chassis.wait_drive();
  spinRoller();
  
  chassis.set_swing_pid(ez::LEFT_SWING, -9, SWING_SPEED);
  chassis.wait_drive();
  
  //move back 2
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  pros::delay(82);
  fire();
  chassis.wait_drive();


  //left swing to -120
  chassis.set_turn_pid(-135, SWING_SPEED);
  chassis.wait_drive();
  //move forward 40 inches
  //intake on
  intakeState = 1;
  pisstake.set_value(1);
  chassis.set_drive_pid(21, 70, true);
  chassis.wait_drive();
  pisstake.set_value(0);
  pros::delay(500);
  chassis.set_drive_pid(23, 90, true);
  chassis.wait_drive();
  //right swing to -38
  chassis.set_turn_pid(-31, TURN_SPEED);
  chassis.wait_drive();
  //momentum shot
  chassis.set_drive_pid(-6, DRIVE_SPEED);
  pros::delay(10);
  fire();
  chassis.wait_drive();

  chassis.set_turn_pid(-75, TURN_SPEED);
  chassis.wait_drive();
  //move forward into low goal
  chassis.set_drive_pid(14.5, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to -10
  chassis.set_turn_pid(-12, TURN_SPEED);
  chassis.wait_drive();
  //move forward into low goal discs
  chassis.set_drive_pid(35, 60);
  chassis.wait_drive();
  pros::delay(500);

  //turn to goal, back up and fire
  chassis.set_turn_pid(-32, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-35, DRIVE_SPEED);
  chassis.wait_drive();
  
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  pros::delay(50);
  fire();
  useAltLimitSwitch = false;
  chassis.wait_drive();

  intakeState = false;
  
  //fire boost piston
  boost.set_value(true);
  pros::delay(100);
  boost.set_value(false);


}

void rightSide(){
  useAltLimitSwitch = true;

  chassis.set_angle(-90);

  chassis.set_drive_pid(-19.5, 100);
  chassis.wait_drive();

  //swing to 180
  chassis.set_turn_pid(-168, TURN_SPEED);
  chassis.wait_drive();
  //move forward into roller
  chassis.set_drive_pid(5, DRIVE_SPEED);
  chassis.wait_drive();
  //spin the roller
  spinRoller();
  pros::delay(100);
  chassis.set_drive_pid(-6, 90);
  fire();
  chassis.wait_drive();
  
  
  //turn into the 3 row
  chassis.set_turn_pid(-50, TURN_SPEED);
  chassis.wait_drive();

  //move forward into the 3 row, intake on
  intakeState = 1;
  chassis.set_drive_pid(63, 70);
  chassis.wait_drive();

  //swing to goal and fire
  chassis.set_swing_pid(ez::LEFT_SWING, -136, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  pros::delay(20);
  fire();
  chassis.wait_drive();

  //move into low goal 3
  chassis.set_drive_pid(14.5, DRIVE_SPEED);
  chassis.wait_drive();
  while (!cata_state) {
    pros::delay(5);
  }
  chassis.set_turn_pid(-165, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(35, 60);
  chassis.wait_drive();
  pros::delay(250);

  //back up and fire
  chassis.set_swing_pid(ez::RIGHT_SWING, -145, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-36, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-5, 127);
  pros::delay(10);
  fire();
  useAltLimitSwitch = false;
  chassis.wait_drive();
  boost.set_value(true);
  pros::delay(50);
  boost.set_value(false);


}

void matchLeftFull() {

  useAltLimitSwitch = true;

  //move into roller and spin it
  chassis.set_drive_pid(7.25, DRIVE_SPEED);
  chassis.wait_drive();
  spinRoller();
  
  chassis.set_swing_pid(ez::LEFT_SWING, -9, SWING_SPEED);
  chassis.wait_drive();
  
  //move back 2
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  pros::delay(82);
  fire();
  chassis.wait_drive();


  //left swing to -120
  chassis.set_turn_pid(-135, SWING_SPEED);
  chassis.wait_drive();
  //move forward 40 inches
  //intake on
  intakeState = 1;
  pisstake.set_value(1);
  chassis.set_drive_pid(21, 70, true);
  chassis.wait_drive();
  pisstake.set_value(0);
  pros::delay(500);
  chassis.set_drive_pid(22, 90, true);
  chassis.wait_drive();
  //right swing to -38
  chassis.set_turn_pid(-31, TURN_SPEED);
  chassis.wait_drive();
  //momentum shot
  chassis.set_drive_pid(-6, DRIVE_SPEED);
  pros::delay(12);
  fire();
  chassis.wait_drive();
  chassis.set_turn_pid(-75, TURN_SPEED);
  chassis.wait_drive();

  //swing right to -135
  chassis.set_swing_pid(ez::RIGHT_SWING, -135, SWING_SPEED);
  chassis.wait_drive();
  
  //move forward 60 with intake and slew on
  chassis.set_drive_pid(57, 75, true);
  chassis.wait_drive();
  //move back 10
  chassis.set_drive_pid(-10, DRIVE_SPEED);
  chassis.wait_drive();
  //swing right to -60
  chassis.set_swing_pid(ez::RIGHT_SWING, -63, SWING_SPEED);
  chassis.wait_drive();
  //move back 7
  chassis.set_drive_pid(-4, 127);
  pros::delay(75);
  fire();
  useAltLimitSwitch = false;
  
  boost.set_value(true);
  chassis.wait_drive();
  //swing right to -110
  chassis.set_swing_pid(ez::RIGHT_SWING, -135, SWING_SPEED);
  chassis.wait_drive();
  boost.set_value(false);
  intakeState = 0;
  //move forward 30
  chassis.set_drive_pid(37, DRIVE_SPEED, true);
  chassis.wait_drive();
  //spin roller
  spinRoller();

  
}

void matchNoAuton() {
  // no auton
}