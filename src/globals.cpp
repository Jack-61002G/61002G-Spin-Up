#include "TaskWrapper.hpp"
#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"
#include <iostream>
#include "Catapult.hpp"

Catapult cata; // create a catapult object


pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor catapultMotor(19, pros::E_MOTOR_GEARSET_36, true);
pros::ADIButton limitButton('A');
pros::ADIButton altLimitButton('E');
pros::Motor intake1(9);
int intakeState = 0;
pros::ADIDigitalOut booster('H');

pros::Motor left_front_motor(12, true);    // port 1, not reversed
pros::Motor left_back_motor(13, true);    // port 2, not reversed
pros::Motor left_top_motor(4, false);     // port 3, reversed
pros::Motor right_top_motor(17, true);    // port 3, reversed
pros::Motor right_back_motor(20, false);   // port 4, reversed
pros::Motor right_front_motor(18, false); // port 2, not reversed

pros::MotorGroup left_side_motors({left_front_motor, left_back_motor,
                                   left_top_motor});
pros::MotorGroup right_side_motors({right_front_motor, right_back_motor,
                                    right_top_motor});

lemlib::Drivetrain_t drivetrain {
    &left_side_motors, // left drivetrain motors
    &right_side_motors, // right drivetrain motors
    11.5625, // track width
    3.25, // wheel diameter
    360 // wheel rpm
};

// inertial sensor
pros::Imu inertial_sensor(10); // port 2

// odometry struct
lemlib::OdomSensors_t sensors{
    nullptr, // vertical tracking wheel 1
    nullptr,              // horizontal tracking wheel 1
    nullptr, // vertical tracking wheel 2
    nullptr, // we don't have a second tracking wheel, so we set it to nullptr
    &inertial_sensor // inertial sensor
};

// forward/backward PID
lemlib::ChassisController_t lateralController {
    14, // kP
    21, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    9 // slew rate
};
 
// turning PID
lemlib::ChassisController_t angularController {
    3.5, // kP
    35, // kD
    1, // smallErrorRange
    50, // smallErrorTimeout
    3, // largeErrorRange
    200, // largeErrorTimeout
    40 // slew rate
};
 
 
// create the chassis
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

int joystickCurve(double input, bool red) {
  int val = 0;
  int t = 6;
  // scale input from -127 to 127 to -100 to 100
  input = input * 100 / 127;

  if (red) {
    val = (std::exp(-t / 10) +
           std::exp((std::abs(input) - 100) / 10) * (1 - std::exp(-t / 10))) *
          input;
  } else {
    // blue
    val = std::exp(((std::abs(input) - 100) * t) / 1000) * input;
  }
  // return value scaled back to -127 to 127
  return val * 127 / 100;
}