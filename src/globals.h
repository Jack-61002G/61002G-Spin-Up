#include "main.h"
#include "okapi/impl/device/motor/motorGroup.hpp"
#include "pros/motors.hpp"
extern okapi::MotorGroup spinnyman;
extern bool flywheel_state;
extern pros::Controller master;
extern bool intake_state;
extern pros::Motor front_intake;
extern pros::Motor gate;
extern bool gate_state;

//odom
extern int degrees;
extern double posX, posY;
extern bool odom_state;