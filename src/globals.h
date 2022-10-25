#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.hpp"


extern bool flywheel_state;
extern pros::Motor catapultMotor;
extern pros::ADIButton limitButton;

extern pros::Motor intake1;
extern pros::Motor intake2;
extern int intakeState;
extern Drive chassis;


extern void cataTask();
extern void intaketoggle();
