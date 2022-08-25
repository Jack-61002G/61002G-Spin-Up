#include "main.h"
#include "globals.h"
#include "okapi/api.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"

void intaketoggle();
void flywheelpid();
void gatetoggle();

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {
  // pros::Task odom(real_Odometry);
  chassis->moveDistance(1_ft);
  chassis->turnAngle(180_deg);
  chassis->moveDistance(1_ft);
}

void opcontrol() {
  chassis->getModel()->arcade(
      master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),
      master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  pros::Task intake(intaketoggle);
  pros::Task flywheel(flywheelpid);
  pros::Task gate(gatetoggle);
}
