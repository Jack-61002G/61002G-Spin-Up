#include "globals.h"
#include "main.h"
#include "pros/rtos.hpp"

void intaketoggle() { // 0 = stop, -1 = intake, 1 = output
  if (intakeState != 0) {

    if (intakeState == 1) {
      intake1.move_voltage(12000);
    } else if (intakeState == -1) {
      intake1.move_voltage(-12000);
    }

  } else {
    intake1.move(0);
  }
}

void spinRoller() {
  intake1.move_relative(1100, 100);
}
