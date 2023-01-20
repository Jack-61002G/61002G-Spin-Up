#include "autons.hpp"
#include "globals.h"
#include "main.h"

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
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, .45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, .45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void even_floor_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
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

  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
}

// Auton Functions

void testCata(){
  cata_override = true;


}

void autonSkillsNew() {


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

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(8, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();
  pros::delay(500);

  chassis.set_swing_pid(ez::LEFT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-53, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, 40);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) { pros::delay(10); }
  catapultMotor.move_voltage(0);

  chassis.set_drive_pid(12, 40);
  chassis.wait_drive();
  chassis.set_drive_pid(49, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(30, 50);
  chassis.wait_drive();

  pros::delay(700);
  intakeState = -1;
  intaketoggle();
  pros::delay(200);
  intakeState = 0;
  intaketoggle();

  chassis.set_drive_pid(-30, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-51, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, 40);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) { pros::delay(10); }
  catapultMotor.move_voltage(0);

  chassis.set_drive_pid(12, 40);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-46, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::RIGHT_SWING, 90, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-63, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(37, 60);
  chassis.wait_drive();

  pros::delay(1000);
  intakeState = -1;
  intaketoggle();
  pros::delay(200);
  intakeState = 0;
  intaketoggle();

  chassis.set_drive_pid(-29, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, -90, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-21, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-97, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, 40);
  chassis.wait_drive();
  
  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) { pros::delay(10); }
  catapultMotor.move_voltage(0);

  chassis.set_drive_pid(12, 40);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(47, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(25, 50);
  chassis.wait_drive();

  pros::delay(1100);
  intakeState = -1;
  intaketoggle();
  pros::delay(200);
  intakeState = 0;
  intaketoggle();

  chassis.set_drive_pid(-25, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_swing_pid(ez::LEFT_SWING, -90, SWING_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-46, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-97, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, 40);
  chassis.wait_drive();
  
  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) { pros::delay(10); }
  catapultMotor.move_voltage(0);

  chassis.set_drive_pid(12, 40);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(54, 75);
  chassis.wait_drive();

  intakeState = -1;
  intaketoggle();
  pros::delay(200);
  intakeState = 0;
  intaketoggle();

  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();
  pros::delay(500);

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();

  // expansion
  pros::ADIDigitalOut piston('B');
  piston.set_value(true);

}

void pushAuton() {

  chassis.set_drive_pid(-20, 60);
  chassis.wait_drive();

}

void autonSkills() {

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();
  spinRoller();
  spinRoller();

  chassis.set_drive_pid(-15, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();
  spinRoller();

  chassis.set_drive_pid(-53, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(98, TURN_SPEED);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) {
    pros::delay(10);
  }
  catapultMotor.move_voltage(0);

  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(36, DRIVE_SPEED);
  chassis.wait_drive();

  intakeState = 0;
  intaketoggle();

  chassis.set_turn_pid(225, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(20, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(318, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) {
    pros::delay(10);
  }
  catapultMotor.move_voltage(0);

  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-35, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(12, DRIVE_SPEED);
  chassis.wait_drive();

  pros::delay(600);
  intakeState = 0;
  intaketoggle();

  chassis.set_drive_pid(-7, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-48, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) {
    pros::delay(10);
  }
  catapultMotor.move_voltage(0);

  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(16, DRIVE_SPEED);
  chassis.wait_drive();

  pros::delay(300);
  intakeState = 0;
  intaketoggle();

  chassis.set_drive_pid(-16, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-48, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(3, DRIVE_SPEED);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) {
    pros::delay(10);
  }
  catapultMotor.move_voltage(0);

  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(66, 80);
  chassis.wait_drive();

  intakeState = 0;
  intaketoggle();

  chassis.wait_drive();
  chassis.set_turn_pid(-90, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(7, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();
  spinRoller();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(24, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();
  spinRoller();

  chassis.set_drive_pid(-12, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(180, TURN_SPEED);
  chassis.wait_drive();

  /*
    chassis.set_turn_pid(-270, TURN_SPEED);
    chassis.wait_drive();
    chassis.set_drive_pid(24, DRIVE_SPEED);
    chassis.wait_drive();

    chassis.set_drive_pid(-6, DRIVE_SPEED);
    chassis.wait_drive();
    chassis.set_turn_pid(90, TURN_SPEED);
    chassis.wait_drive();
    chassis.set_drive_pid(-72, DRIVE_SPEED);
    chassis.wait_drive();

    // shoot
    catapultMotor.move_voltage(12000);
    pros::delay(500);
    while (limitButton.get_value() == false) { pros::delay(10); }
    catapultMotor.move_voltage(0);

    chassis.set_turn_pid(135, TURN_SPEED);
    chassis.wait_drive();
  */

  // expansion
  pros::ADIDigitalOut piston('B');
  piston.set_value(true);
}

void matchRight() {

  chassis.set_drive_pid(30, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-20, DRIVE_SPEED);
  chassis.wait_drive();
}

void matchLeftFull() {

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();
  spinRoller();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(43, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-42, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) {
    pros::delay(10);
  }
  catapultMotor.move_voltage(0);

  chassis.set_turn_pid(-30, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(12, DRIVE_SPEED);
  chassis.wait_drive();

  pros::delay(600);
  intakeState = 0;
  intaketoggle();

  chassis.set_drive_pid(-7, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-48, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) {
    pros::delay(10);
  }
  catapultMotor.move_voltage(0);

  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(16, DRIVE_SPEED);
  chassis.wait_drive();

  pros::delay(300);
  intakeState = 0;
  intaketoggle();

  chassis.set_drive_pid(-16, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-48, TURN_SPEED);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) {
    pros::delay(10);
  }
  catapultMotor.move_voltage(0);
}

void rollerAuto() {  

  chassis.set_drive_pid(2.5, DRIVE_SPEED);
  chassis.wait_drive();

  intake1.move_relative(500, 100);
  
  pros::delay(500);

  chassis.set_drive_pid(-2, DRIVE_SPEED);
  chassis.wait_drive();

}

void matchLeftPartial() {

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();
  spinRoller();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(12, DRIVE_SPEED);
  chassis.wait_drive();
}

void matchAutonWP() {

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();
  spinRoller();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(40, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(43, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(10, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-42, TURN_SPEED);
  chassis.wait_drive();

  // shoot
  catapultMotor.move_voltage(12000);
  pros::delay(500);
  while (limitButton.get_value() == false) {
    pros::delay(10);
  }
  catapultMotor.move_voltage(0);

  chassis.set_drive_pid(-3, DRIVE_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-130, TURN_SPEED);
  chassis.wait_drive();

  intakeState = 1;
  intaketoggle();

  chassis.set_drive_pid(66, 80);
  chassis.wait_drive();

  intakeState = 0;
  intaketoggle();

  chassis.set_turn_pid(-180, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(6, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();

  chassis.set_drive_pid(-6, DRIVE_SPEED);
  chassis.wait_drive();
}

void matchNoAuton() {
  // no auton
}

void skillsSafe() {

  chassis.set_drive_pid(4, DRIVE_SPEED);
  chassis.wait_drive();

  spinRoller();
  spinRoller();

  chassis.set_drive_pid(-4, DRIVE_SPEED);
  chassis.wait_drive();
  chassis.set_turn_pid(35, TURN_SPEED);
  chassis.wait_drive();

  pros::delay(2000);

  // expansion
  pros::ADIDigitalOut piston('B');
  piston.set_value(true);
}