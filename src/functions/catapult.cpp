#include "main.h"
#include "pros/rtos.hpp"

void cataTask() {
        while (true) {
            if (!limitButton.get_value()) {
                catapultMotor.move(127);
        } else if (master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
            catapultMotor.move_voltage(127);
        }
        pros::delay(10);
    }
}