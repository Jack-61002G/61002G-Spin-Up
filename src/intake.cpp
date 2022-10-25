#include "globals.h"
#include "main.h"

void intaketoggle() {
  if (intakeState != 0) {

    if (intakeState == 1) {
      intake1.move_voltage(10000);
      intake2.move_voltage(-10000);
    }
    else if (intakeState == -1) {
      intake1.move_voltage(-10000);
      intake2.move_voltage(10000);
    }

  } else {intake1.move(0); intake2.move(0);}
}