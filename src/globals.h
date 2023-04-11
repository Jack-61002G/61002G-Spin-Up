#pragma once

#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "sylib/motor.hpp"

extern pros::Motor intake;
extern int intakeState;
extern Drive chassis;
extern sylib::Motor flywheel;

extern void fire();
