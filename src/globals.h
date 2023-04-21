#pragma once

#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "pros/rotation.hpp"


extern bool flywheel_state;
extern pros::Motor catapultMotor;
extern pros::ADIDigitalOut pisstake;
extern string whatTheLightDoin;
extern bool cata_override;
extern pros::Motor intake1;
extern pros::Motor intake2;
extern int intakeState;
extern bool useAltLimitSwitch;
extern Drive chassis;
extern pros::ADIDigitalOut boost;
extern pros::Rotation catarotation;
extern bool cata_state;

extern sylib::Addrled leftSideLights;
extern sylib::Addrled rightSideLights;
extern sylib::Addrled intakeLights;
extern sylib::Addrled rearLights;

extern void light_task_fn();
extern void cata_task_fn();
extern void intake_task_fn();
extern void spinRoller();
extern void fire();
