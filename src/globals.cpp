#include "EZ-Template/util.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.h"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor catapultMotor(19, pros::E_MOTOR_GEARSET_36, true);
pros::Rotation catarotation(7);
pros::Motor intake1(9);
pros::ADIDigitalOut boost('h');
pros::ADIDigitalOut pisstake('c');

//creating led objects
sylib::Addrled rightSideLights = sylib::Addrled(22, 2, 48); //change port numbers later, idk what ports are open
sylib::Addrled leftSideLights = sylib::Addrled(22, 4, 48);
sylib::Addrled rearLights = sylib::Addrled(22, 5, 10);
sylib::Addrled intakeLights = sylib::Addrled(22, 6, 28);

//declaring variables
bool initializing = true;
int intakeState = 0;
bool useAltLimitSwitch = false;
void cataTask();
void intaketoggle();
void intakeTask();
bool shouldSpin = true;
bool cata_override = false;
bool cata_state = true;
double targetvalue = 70; //   <------- cata target position

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

void light_task_fn() {

  int rotation_pixel{0};
  int cata_count{2};
  int init_count{0};
  int intake_count{0};

  leftSideLights.clear();
  rightSideLights.clear();
  rearLights.set_all(sylib::Addrled::rgb_to_hex(160, 32, 240));
  intakeLights.set_all(sylib::Addrled::rgb_to_hex(160, 32, 240));

  while (true) {
    
    if (master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) && master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
      leftSideLights.set_all(sylib::Addrled::rgb_to_hex(160, 32, 240));
      rightSideLights.set_all(sylib::Addrled::rgb_to_hex(160, 32, 240));
      pros::delay(200);
      leftSideLights.set_all(sylib::Addrled::rgb_to_hex(80, 16, 120));
      rightSideLights.set_all(sylib::Addrled::rgb_to_hex(80, 16, 120));
      pros::delay(800);
    }

    if (pros::competition::get_status() & COMPETITION_DISABLED && !initializing) {// rotating effect when the robot is disabled
      leftSideLights.clear();
      rightSideLights.clear();
      leftSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), rotation_pixel);
      leftSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), rotation_pixel + 1);
      leftSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), rotation_pixel + 2);
      leftSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), rotation_pixel + 3);
      leftSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), rotation_pixel + 4);
      rightSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), 48 - rotation_pixel);
      rightSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), 47 - rotation_pixel);
      rightSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), 46 - rotation_pixel);
      rightSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), 45 - rotation_pixel);
      rightSideLights.set_pixel(sylib::Addrled::rgb_to_hex(160, 32, 240), 44 - rotation_pixel);
      rotation_pixel++;
      if (rotation_pixel >= 52) {rotation_pixel = -4;}
    }
    else {
      leftSideLights.set_all(sylib::Addrled::rgb_to_hex(80, 16, 120));
      rightSideLights.set_all(sylib::Addrled::rgb_to_hex(80, 16, 120));

      if (intakeState == 0) {// flowing lights when intaking
        intakeLights.set_all(sylib::Addrled::rgb_to_hex(160, 32, 240));
      } else if (intakeState == 1) {
        intakeLights.set_all(sylib::Addrled::rgb_to_hex(110, 32, 255));
      } else {
        intakeLights.set_all(sylib::Addrled::rgb_to_hex(240, 32, 180));
      }

      if (cata_state == false) {// lights fill up when cata is returning
        leftSideLights.clear();
        rightSideLights.clear();
        for (int i = 0; i <= cata_count; i++) {
          leftSideLights.set_pixel(sylib::Addrled::rgb_to_hex(80, 16, 120), i);
          rightSideLights.set_pixel(sylib::Addrled::rgb_to_hex(80, 16, 120), i);
        } cata_count++;
      } else {cata_count = 2;}

      if (initializing) {
        leftSideLights.clear();
        rightSideLights.clear();
        for (int i = 0; i <= init_count; i++) {
          leftSideLights.set_pixel(sylib::Addrled::rgb_to_hex(80, 16, 120), i);
          rightSideLights.set_pixel(sylib::Addrled::rgb_to_hex(80, 16, 120), i);
        } init_count++;
        pros::delay(28);
      } else {init_count = 0;}

    }
    pros::delay(30);
  }
}



void cata_task_fn() {
  
  while (true) {

    targetvalue = useAltLimitSwitch ? 73.25 : 71;

    int pos = catarotation.get_angle() / 100;
    if ((pos < targetvalue || pos > 300)) {
      // move catapult down until its reached loading position
      catapultMotor = 127;
      cata_state = false;

    } else if (!cata_override && catarotation.get_position() >= targetvalue) {
      // hold catapult down
      catapultMotor = 0;
      cata_state = true;
    }
    pros::delay(10);
  }
}



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
