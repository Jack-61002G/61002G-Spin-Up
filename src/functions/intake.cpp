#include "globals.hpp"
#include "main.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

void intaketoggle() {
  if (intakeState != 0) {

    if (intakeState == 1) {
      intake1.move(127);
      intake2.move(127);
    }
    else if (intakeState == -1) {
      intake1.move(-127);
      intake2.move(-127);
    }

  } else {intake1.move(0); intake2.move(0);}
}