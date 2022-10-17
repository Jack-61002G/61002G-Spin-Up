#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "ryanlib/api.hpp"
#include "globals.h"
using namespace okapi;

void initialize() {}

void disabled() {} 

void competition_initialize() {}

void autonomous();

void catadegrees();

void opcontrol() {
  
  auto model = chassis->getModel();
  bool cataState = true;
  
  while (true) {

    if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)) {
      if (intakeState == 0) {
        intakeState = -1;
        intaketoggle();
      } else {intakeState = 0; intaketoggle();}
    } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R2)) {
      if (intakeState == 0) {
        intakeState = 1;
        intaketoggle();
      } else {intakeState = 0; intaketoggle();}
    }


    if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L1) && (cataState == true)){
        catapultMotor.move_voltage(12000);

    } else if (limitButton.get_value() == false) { 
        //move catapult down until its reached loading position
        catapultMotor.move_voltage(12000);
        cataState = false;
    } else {
        catapultMotor.move_voltage(0);
        cataState = true;
    }
    model->curvature(master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y),
                     master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X), 0.05);
    pros::delay(10);
  }
}
