#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor catapultMotor(19, pros::E_MOTOR_GEARSET_36, true);
pros::ADIButton limitButton('A');
pros::Motor intake1(9);
int intakeState = 0;

void cataTask();
void intaketoggle();