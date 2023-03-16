#pragma once

#include "main.h"
#include "Catapult.hpp"
#include "globals.h"
#include "TaskWrapper.hpp"


  void Catapult::fire() {
    cata_override = true;
    catapultMotor = 127;
    pros::delay(250);
    cata_override = false;
    state = false;
  }

  void Catapult::loop(){

    while (true) {
      if (useAltLimitSwitch) {
        if ((limitButton.get_value() == false)) {
          // move catapult down until its reached loading position
          catapultMotor = 127;

        } else if (!cata_override && limitButton.get_value()) {
          catapultMotor = 0;
          state = true;
        }
      } else {
        if ((limitButton.get_value() == false)) {
          // move catapult down until its reached loading position
          catapultMotor = 127;

        } else if (!cata_override && limitButton.get_value()) {
          catapultMotor = 0;
          state = true;
        }
      }
      pros::delay(10);
    }
  }

  bool Catapult::getState() {
    return state;
  }