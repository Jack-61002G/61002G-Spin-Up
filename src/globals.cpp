#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor catapultMotor(19, pros::E_MOTOR_GEARSET_36, true);
pros::ADIButton limitButton('A');
pros::ADIButton altLimitButton('E');
pros::Rotation catarotation(7);
pros::Motor intake1(9);
bool useAltLimitSwitch = false;
pros::ADIDigitalOut boost('h');

// Chassis constructor
Drive chassis(
    // Left Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    {-12, -13, 4}

    // Right Chassis Ports (negative port will reverse it!)
    //   the first port is the sensored port (when trackers are not used!)
    ,
    {18, -17, 20}

    // IMU Port
    ,
    10

    // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
    //    (or tracking wheel diameter)
    ,
    3.25

    // Cartridge RPM
    //   (or tick per rotation if using tracking wheels)
    ,
    600

    // External Gear Ratio (MUST BE DECIMAL)
    //    (or gear ratio of tracking wheel)
    // eg. if your drive is 84:36 where the 36t is powered, your RATIO would
    // be 2.333. eg. if your drive is 36:60 where the 60t is powered, your RATIO
    // would be 0.6.
    ,
    1.666

    // Uncomment if using tracking wheels
    /*
    // Left Tracking Wheel Ports (negative port will reverse it!)
    // ,{1, 2} // 3 wire encoder
    // ,8 // Rotation sensor

    // Right Tracking Wheel Ports (negative port will reverse it!)
    // ,{-3, -4} // 3 wire encoder
    // ,-9 // Rotation sensor
    */

    // Uncomment if tracking wheels are plugged into a 3 wire expander
    // 3 Wire Port Expander Smart Port
    // ,1
);



void cataTask();
void intaketoggle();
bool cata_override = false;
bool cata_state = false;
int targetvalue = 70; //   <------- cata target position

void cata_task_fn() {
  
  while (true) {

    targetvalue = useAltLimitSwitch ? 72 : 69;

    int pos = catarotation.get_angle() / 100;
    if ((pos < targetvalue)) {
      // move catapult down until its reached loading position
      catapultMotor = 127;
      cata_state = false;

    } else if (!cata_override && catarotation.get_position() >= targetvalue) {
      catapultMotor = 0;
      cata_state = true;
    }
    pros::delay(10);
  }
}

void intakeTask();
int intakeState = 0;
bool shouldSpin = true;

void intake_task_fn() {
  while (true) {

    if(shouldSpin) {

    //take input
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
      if (intakeState == 0) {intakeState = -1;}
      else {intakeState = 0;}}
    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
      if (intakeState == 0) {intakeState = 1;}
      else {intakeState = 0;}}

    //apply change to motors
    if (intakeState == 1 && cata_state) {
      intake1.move_voltage(12000);}
    else if (intakeState == -1 && cata_state) {
      intake1.move_voltage(-12000);}
    else {
      intake1.move_voltage(0);
    }
      
    if (!cata_state) {intake1.move_voltage(0);}}
      
    pros::delay(5);
  }
}

void spinRoller() {
  shouldSpin = false;
  intake1.move_relative(1100, 100);
  pros::delay(500);
  shouldSpin = true;
}

void fire() {
  cata_override = true;
  catapultMotor = 127;
  pros::delay(250);
  cata_override = false;
  cata_state = false;
}

void fireAsync() {
  cata_override = true;
  while (limitButton.get_value() == true) {
    catapultMotor = 127;
  }
  cata_override = false;
  cata_state = false;
}
