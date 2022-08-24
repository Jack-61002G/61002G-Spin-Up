#include "main.h"
#include "okapi/api.hpp"
#include "globals.h"
#include "pros/misc.h"
#include "pros/rtos.hpp"

std::shared_ptr<ChassisController> myChassis =
  ChassisControllerBuilder()
    .withMotors({1, 2}, {-3, -4})
    // Green gearset, 4 in wheel diam, 11.5 in wheel track
    .withDimensions(AbstractMotor::gearset::green, {{4_in, 11.5_in}, imev5GreenTPR})
	.withGains(
        {0.001, 0, 0.0001}, // Distance controller gains
        {0.001, 0, 0.0001}, // Turn controller gains
        {0.001, 0, 0.0001}  // Angle controller gains (helps drive straight)
    )
    .build();

std::shared_ptr<AsyncMotionProfileController> profileController =
  AsyncMotionProfileControllerBuilder()
    .withLimits({
      1.0, // Maximum linear velocity of the Chassis in m/s
      2.0, // Maximum linear acceleration of the Chassis in m/s/s
      10.0 // Maximum linear jerk of the Chassis in m/s/s/s
    })
    .withOutput(myChassis)
    .buildMotionProfileController();

void intaketoggle();
void flywheelpid();
void gatetoggle();

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	profileController->generatePath({{0_ft, 0_ft, 0_deg},{3_ft, 0_ft, 0_deg}},"A");
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	profileController->setTarget("A"); 
}

void opcontrol() {
   myChassis->getModel()->arcade(master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X),
                                          master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y));
  pros::Task intake(intaketoggle);
  pros::Task flywheel(flywheelpid);
  pros::Task gate(gatetoggle);
}
