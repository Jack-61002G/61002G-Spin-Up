#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor catapultMotor(19, pros::E_MOTOR_GEARSET_36, true);
pros::ADIButton limitButton('A');
pros::Motor intake1(9);
int intakeState = 0;
pros::ADIDigitalOut booster('H');

pros::Motor left_front_motor(7, true); // port 1, not reversed
pros::Motor left_back_motor(11, true); // port 2, not reversed
pros::Motor left_top_motor(6, false); // port 3, reversed
pros::Motor right_top_motor(20, true); // port 3, reversed
pros::Motor right_back_motor(8, false); // port 4, reversed
pros::Motor right_front_motor(18, false); // port 2, not reversed


pros::MotorGroup left_side_motors({left_front_motor, left_back_motor, left_top_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor, right_top_motor});

// left tracking wheel encoder
pros::ADIEncoder right_enc('E', 'F', true); // ports A and B, reversed
// right tracking wheel encoder
// back tracking wheel encoder
pros::ADIEncoder back_enc('C', 'D', false); // ports C and D, not reversed
 
// left tracking wheel
lemlib::TrackingWheel left_tracking_wheel(&right_enc, 2.77, .375); // 2.75" wheel diameter, -4.6" offset from tracking center
lemlib::TrackingWheel back_tracking_wheel(&back_enc, 2.76, -3.75); // 2.75" wheel diameter, 4.5" offset from tracking center
 
// inertial sensor
pros::Imu inertial_sensor(17); // port 2
 
// odometry struct
lemlib::OdomSensors_t sensors {
    &left_tracking_wheel, // vertical tracking wheel 1
    nullptr, // horizontal tracking wheel 1
    &back_tracking_wheel, // vertical tracking wheel 2
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};
 
// forward/backward PID
lemlib::ChassisController_t lateralController {
    9, // kP
    20, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500 // largeErrorTimeout
};
 
// turning PID
lemlib::ChassisController_t angularController {
    2, // kP
    13, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500 // largeErrorTimeout
};
 
// track width
float track_width = 11.5625; // 15.5" track width
 
// create the chassis object
lemlib::Chassis chassis(&left_side_motors, &right_side_motors, track_width, lateralController, angularController, sensors);


void cataTask();
void intaketoggle();
bool cata_override = false;
bool state = false;

void cata_task_fn() {
  
  while (true) {

    if ((limitButton.get_value() == false) && state == false) {
      // move catapult down until its reached loading position
      catapultMotor = 127;

    } else if (!cata_override && limitButton.get_value()) {
      catapultMotor = 0;
      state = true;
      booster.set_value(0);
    }

    pros::delay(10);
  }
}

void fire(bool release) {
  cata_override = true;
  catapultMotor = 127;
  pros::delay(500);
  if (release) {
  booster.set_value(1);
  }
  cata_override = false;
  state = false;
}

int joystickCurve(double input, bool red) {
  int val = 0;
  int t = 9;
  //scale input from -127 to 127 to -100 to 100
  input = input * 100 / 127;

  if(red){
    val = (std::exp(-t/10)+std::exp((std::abs(input)-100)/10)*(1-std::exp(-t/10))) * input;
  }else{
    //blue
    val = std::exp(((std::abs(input)-100)*t)/1000) * input;
  }
  //return value scaled back to -127 to 127
  return val * 127 / 100;

}