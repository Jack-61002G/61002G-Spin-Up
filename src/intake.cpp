#include "globals.h"
#include "main.h"

void intaketoggle() {
  if (intakeState != 0) {

    if (intakeState == 1) {
      intake1.move_voltage(12000);
    }
    else if (intakeState == -1) {
      intake1.move_voltage(-12000);
    }

  } else {intake1.move(0);}
}

void spinRoller() {
  intake1.move_voltage(12000);
  pros::delay(250);
  intake1.move_voltage(0);
}
