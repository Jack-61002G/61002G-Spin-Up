#include "main.h"
#include "okapi/api.hpp"
#include "pros/rtos.hpp"
#include "ryanlib/api.hpp"
#include "globals.hpp"
using namespace okapi;


std::shared_ptr<ChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors({-11, -12}, {19, 20})
        // {motor cartridge, wheel gear / motor gear}, {{wheel diameter, track
        // diameter} imev5<cart>TPR}
        // {motor cartridge, wheel gear / motor gear}, {{wheel diameter, track diameter} imev5<cart>TPR}
        .withDimensions({AbstractMotor::gearset::blue, 84.0/36.0}, {{4.125_in, 1_ft}, imev5BlueTPR}) 
        .build();

void initialize() { pros::lcd::initialize(); }

void disabled() {} 

void competition_initialize() {}

void autonomous() {
  // TEST FUNCTION
  profiler->setTarget(-6_ft);
  profiler->waitUntilSettled();
  profiler->setTarget(180_deg);
  profiler->waitUntilSettled();
  profiler->setTarget(-6_ft);
}

void opcontrol() {
  pros::Task intake_task(intaketoggle);
  pros::Task flywheel_controller(flywheelpid);

  Controller master(ControllerId::master);
  auto model = chassis->getModel();
  
  while (true) {
    model->curvature(master.getAnalog(ControllerAnalog::leftY),
                     master.getAnalog(ControllerAnalog::rightX), 0.05);
    pros::delay(10);
  }
}
