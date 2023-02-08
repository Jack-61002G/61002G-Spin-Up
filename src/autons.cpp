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
    95; // This is 110/127 (around 87% of max speed).  We don't suggest making
        // this 127. If this is 127 and the robot tries to heading correct, it's
        // only correcting by making one side slower.  When this is 87%, it's
        // correcting by making one side faster and one side slower, giving
        // better heading correction.
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

// It's best practice to tune constants when the robot is empty and with heavier
// game objects, or with lifts up vs down. If the objects are light or the cog
// doesn't change much, then there isn't a concern here.

void garage_constants() {
  chassis.set_slew_min_power(55, 55);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, .45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, .45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void exit_condition_defaults() {
  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);
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

void rightPushRoller() {

  chassis.set_drive_pid(-20, 60);
  chassis.wait_drive();

  chassis.set_drive_pid(68, 80);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(6, 60);
  chassis.wait_drive();

  spinRoller();

}

void rightRoller() {

  chassis.set_drive_pid(48, 80);
  chassis.wait_drive();

  chassis.set_turn_pid(90, 80);
  chassis.wait_drive();

  chassis.set_drive_pid(6, 60);
  chassis.wait_drive();

  spinRoller();

}

void autonSkillsNew() {

  pros::ADIDigitalOut piston('B');
  piston.set_value(false);

  chassis.set_drive_pid(2.5, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();
  pros::delay(500);

  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 105, SWING_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(25, 75);
  chassis.wait_drive();

  pros::delay(300);
  intakeState = -1;
  intaketoggle();
  pros::delay(200);
  intakeState = 0;
  intaketoggle();

  chassis.set_turn_pid(85, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(11, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();
  pros::delay(500);

  chassis.set_swing_pid(ez::LEFT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-53, DRIVE_SPEED);
  chassis.wait_drive();

  fire();

  //move into 3 stack
  chassis.set_drive_pid(33, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to -90
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();
  //turn intake on and move forward slowly
  intakeState = 1;
  intaketoggle();
  chassis.set_drive_pid(35, 30);
  chassis.wait_drive();
  pros::delay(200);
  //move back to the goal
  chassis.set_drive_pid(-40, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to face goal
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 0;
  intaketoggle();
  //move back to goal
  chassis.set_drive_pid(-33, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  //fire
  fire();

  //turn 45 deg to 3 row
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  //intake on
  intakeState = 1;
  intaketoggle(); 

  //move forward into disc
  chassis.set_drive_pid(27, 50);
  chassis.wait_drive();
  //turn to 135 deg
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  //move forward into 3 row
  chassis.set_drive_pid(45, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to 180 deg
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  //move forward towards wall
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();
  //turn intake off
  intakeState = 0;
  intaketoggle();
  //turn to 90 deg
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  //move back to goal
  chassis.set_drive_pid(-8.5, DRIVE_SPEED);
  chassis.wait_drive();
  //fire
  fire();
  //move forward 5

  /* no more 3 stack
  //turn to -45 deg
  chassis.set_turn_pid(-40, TURN_SPEED);
  chassis.wait_drive();
  //turn intake on and then move forward into 3 stack at 40 speed
  intakeState = 1;
  intaketoggle();
  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(30, 30);
  chassis.wait_drive();
  //move back to goal
  chassis.set_drive_pid(-50, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to -90 deg
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  //fire
  fire(); */

  //move forward 40 inches
  chassis.set_drive_pid(43, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to 180 deg
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  //move forward 6 inches and spin roller
  chassis.set_drive_pid(9.5, DRIVE_SPEED);
  chassis.wait_drive();
  spinRoller();
  pros::delay(500);
  // move back 3 inches and turn to 0 deg
  chassis.set_drive_pid(-4.5, DRIVE_SPEED);
  chassis.wait_drive(); 
  chassis.set_turn_pid(-10, TURN_SPEED);
  chassis.wait_drive();
  //move forward 7 inches and turn intake on
  intakeState = 1;
  intaketoggle();
  chassis.set_drive_pid(14, DRIVE_SPEED);
  chassis.wait_drive();
  //move forward 20 inches
  chassis.set_drive_pid(25, 70);
  chassis.wait_drive();
  //move back 30
  chassis.set_drive_pid(-13.5, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to -90 deg and turn intake off
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  intakeState = 0;
  intaketoggle();
  //move forward 29
  chassis.set_drive_pid(27, DRIVE_SPEED);
  chassis.wait_drive();
  //spin roller
  spinRoller();
  pros::delay(500);
  //swing left to 180
  chassis.set_swing_pid(ez::LEFT_SWING, -180, SWING_SPEED);
  chassis.wait_drive();
  //move back 42
  chassis.set_drive_pid(-40, DRIVE_SPEED);
  chassis.wait_drive();
  //fire
  fire();
  //turn to 135 deg
  chassis.set_turn_pid(135, TURN_SPEED);
  chassis.wait_drive();
  //turn on intake
  intakeState = 1;
  intaketoggle();
  //move forward into disc
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-5, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to 45 deg
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();
  //move forward into 3 row
  chassis.set_drive_pid(45, 50);
  chassis.wait_drive();
  //turn to -20 deg
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  //move forward towards wall
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to 90 deg
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  //move back into goal
  chassis.set_drive_pid(-8.5, DRIVE_SPEED);
  chassis.wait_drive();
  //fire
  fire();

  
  //turn to 135 deg
  chassis.set_turn_pid(127, TURN_SPEED);
  chassis.wait_drive();
  //turn intake on and then move forward into 3 stack at 40 speed
  intakeState = 1;
  intaketoggle();
  chassis.set_drive_pid(25, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(15, 35);
  chassis.wait_drive();
  //move back to goal
  chassis.set_drive_pid(-43, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to -90 deg
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  //fire
  fire();

  chassis.set_turn_pid(92, TURN_SPEED);
  //move forward 50 inches
  chassis.set_drive_pid(66, DRIVE_SPEED);
  chassis.wait_drive();
  //turn to 45 deg
  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  //fire endgame piston
  piston.set_value(true);
  //PLEASE FOR THE LOVE OF GOD DO NOT FORGET TO ADD AND TEST THIS BEFORE ROBOBASH

  




}

void pushAuton() {

  chassis.set_drive_pid(-20, 60);
  chassis.wait_drive();

}

void matchLeftFull() {

  //move into roller and spin it
  chassis.set_drive_pid(2, DRIVE_SPEED);
  chassis.wait_drive();
  spinRoller();
  chassis.wait_drive();
  
  //right swing to face 45 degrees
  chassis.set_swing_pid(ez::RIGHT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();
  //back up to the middle of the field

  chassis.set_drive_pid(-55, DRIVE_SPEED);
  chassis.wait_drive();
  //turn left 90 degrees to face the goal
  chassis.set_swing_pid(ez::LEFT_SWING, -40, SWING_SPEED);
  chassis.wait_drive();
  //fire
  fire();
  //swing forwards and to the left
  intakeState = 1;
  intaketoggle();
  chassis.set_swing_pid(ez::RIGHT_SWING, -135, SWING_SPEED);
  chassis.wait_drive();
  //move towards the roller
  chassis.set_drive_pid(58, DRIVE_SPEED);
  chassis.wait_drive();
  intakeState = 0;
  intaketoggle();
  //swing to -90 degrees
  chassis.set_swing_pid(ez::LEFT_SWING, -90, SWING_SPEED);
  chassis.wait_drive();
  //spin the roller
  intake1.move_relative(600, 100);
  
}

void rollerAuto() {  

  chassis.set_drive_pid(2.5, DRIVE_SPEED);
  chassis.wait_drive();

  intake1.move_relative(500, 100);
  
  pros::delay(500);

  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();

}

void matchNoAuton() {
  // no auton
}