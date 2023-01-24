#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motors.hpp"


extern bool flywheel_state;
extern pros::Motor catapultMotor;
extern pros::ADIButton limitButton;

extern pros::Motor intake1;
extern pros::Motor intake2;
extern int intakeState;
extern pros::Controller master;


extern void cata_task_fn();
extern void intaketoggle();
extern void spinRoller();
extern bool cata_override;
