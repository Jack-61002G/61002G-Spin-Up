#pragma once

#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"


extern bool flywheel_state;
extern pros::Motor catapultMotor;
extern pros::ADIButton limitButton;
extern bool cata_override;
extern pros::Motor intake1;
extern pros::Motor intake2;
extern int intakeState;
extern bool useAltLimitSwitch;
extern Drive chassis;
extern pros::ADIDigitalOut boost;
extern bool state;


extern void cata_task_fn();
extern void intaketoggle();
extern void spinRoller();
extern void fire();
