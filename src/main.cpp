#include "main.h"
#include "ryanlib/api.hpp"
using namespace okapi;

void initialize() {}

void disabled() {} 

void competition_initialize() {}

void autonomous() {}

void opcontrol() {

  pros::Task catapult (cataTask);
  Controller master(ControllerId::master);
  auto model = chassis->getModel();
  
  while (true) {
    model->curvature(master.getAnalog(ControllerAnalog::leftY),
                     master.getAnalog(ControllerAnalog::rightX), 0.05);
    pros::delay(10);
  }
}
