#include "main.h"
#include "pros/motors.hpp"
okapi::MotorGroup spinnyman({-1, 2});
pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor front_intake(9);
pros::Motor gate(8);
bool flywheel_state{false};
bool intake_state{true};
bool gate_state{true};

// odom

int degrees;
double posX, posY;
double head;
bool odom_state{false};