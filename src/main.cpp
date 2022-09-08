#include "main.h"
#include "globals.h"
#include "okapi/api.hpp"
#include "pros/misc.h"
#include "pros/motors.hpp"
#include "pros/rtos.hpp"

void flywheelpid();
void intaketoggle();
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
  std::shared_ptr<ChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors({-6, -9}, {14, 15}) // left motor is 1, right motor is 2 (reversed)
        .withSensors(
            ADIEncoder{'A', 'B'}, // left encoder in ADI ports A & B
            ADIEncoder{'C', 'D',
                       true},    // right encoder in ADI ports C & D (reversed)
            ADIEncoder{'E', 'F'} // middle encoder in ADI ports E & F
            )
        // green gearset, tracking wheel diameter (2.75 in), track (7 in), and
        // TPR (360) 1 inch middle encoder distance, and 2.75 inch middle wheel
        // diameter
        .withDimensions(AbstractMotor::gearset::green,
                        {{2.75_in, 7_in, 6_in, 2.75_in}, quadEncoderTPR})
        .withOdometry()   // use the same scales as the chassis (above)
        .buildOdometry(); // build an odometry chassis

  // pros::Task odom(real_Odometry);
  chassis->moveDistance(1_ft);
  chassis->turnAngle(180_deg);
  chassis->moveDistance(1_ft);
}

void opcontrol() {


  pros::Task fly(flywheelpid);
  pros::Task intake(intaketoggle);

  pros::Motor left1(6, true);
  pros::Motor left2(9, true);
  pros::Motor_Group left_drive ({left1, left2});

  pros::Motor right1(14);
  pros::Motor right2(15);
  pros::Motor_Group right_drive ({right1, right2});

  while (1 == 1) {
    left_drive.move((master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) + master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)));
    right_drive.move((master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y) - master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X)));
  }
}