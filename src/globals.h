#pragma once

#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"


extern bool flywheel_state;
extern pros::Motor catapultMotor;
extern pros::ADIButton limitButton;
extern bool cata_override;
extern pros::Motor intake1;
extern pros::Motor intake2;
extern int intakeState;
extern pros::Controller master;

extern pros::MotorGroup left_side_motors;
extern pros::MotorGroup right_side_motors;

extern lemlib::Chassis chassis;


extern void cata_task_fn();
extern void intaketoggle();
extern void spinRoller();
extern void fire();
extern int joystickCurve(double input, bool red);
