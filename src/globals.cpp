#include "main.h"
#include "pros/motors.hpp"
okapi::MotorGroup spinnyman({-8, 10});
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor front_intake(19);
pros::Motor gate(16);
bool flywheel_state{false};
bool intake_state{true};
bool gate_state{true};

// odom

int degrees;
double posX, posY;
double head;
bool odom_state{false};