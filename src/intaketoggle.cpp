#include "main.h"
#include "globals.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

void intaketoggle() {

    while (true) {
        if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L2)) {
            if (intake_state) {
                front_intake.move(127);
                intake_state = !intake_state;
            }
            else {
                front_intake.move(0);
                intake_state = !intake_state;
            }
        }
        pros::delay(10);
    }
}