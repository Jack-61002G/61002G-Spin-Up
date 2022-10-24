#include "main.h"
#include "globals.h"

void cataTask() {
        while (1 == 1) {
            if (!limitButton.get_value()) {
                catapultMotor.move(127);
        } 
        if (master.get_digital(pros::E_CONTROLLER_DIGITAL_R1) && limitButton.get_value()) {
            catapultMotor.move_voltage(127);
        } else {catapultMotor.move(0);}
        pros::delay(10);
    }
}