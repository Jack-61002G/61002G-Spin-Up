#include "main.h"
#include "pros/adi.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"
#include "ryanlib/api.hpp"
using namespace okapi;

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor catapultMotor(19, pros::E_MOTOR_GEARSET_36, true);
pros::ADIButton limitButton('A');
pros::Motor intake1(11);
pros::Motor intake2(12);
int intakeState = 0;

void cataTask();
void intaketoggle();

// odom

int degrees;
double posX, posY;
double head;
bool odom_state{false};

//chassis

// Chassis' max velocity, acceleration, and jerk
ProfileConstraint moveLimit({5.3_ftps, 6_ftps2, 27_ftps3});

//FFVelocityController leftController(0.23, .025, .01, 1.8, .1);
//FFVelocityController rightController(0.23, .025, .01, 1.8, .1);

std::shared_ptr<ChassisController> chassis =
    ChassisControllerBuilder()
        .withMotors({-18, -1}, {13, 14})
        // {motor cartridge, wheel gear / motor gear}, {{wheel diameter, track
        // diameter} imev5<cart>TPR}
        // {motor cartridge, wheel gear / motor gear}, {{wheel diameter, track diameter} imev5<cart>TPR}
        .withDimensions({AbstractMotor::gearset::blue, 84.0/36.0}, {{4.125_in, 1_ft}, imev5BlueTPR}) 
        .build();

std::shared_ptr<AsyncMotionProfiler> profiler =
    AsyncMotionProfilerBuilder()
        .withOutput(chassis)
        .withProfiler(std::make_unique<SCurveMotionProfile>(moveLimit))
        //.withLinearController(leftController, rightController)
        .build();