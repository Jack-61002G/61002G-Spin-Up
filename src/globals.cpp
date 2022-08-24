#include "main.h"
#include "pros/motors.hpp"
okapi::MotorGroup spinnyman ({-9, 10});
pros::Controller master (pros::E_CONTROLLER_MASTER);
pros::Motor front_intake (6);
pros::Motor gate (1, pros::E_MOTOR_GEARSET_18, false, pros::E_MOTOR_ENCODER_DEGREES);
bool flywheel_state{false};
bool intake_state{true};
bool gate_state{true};