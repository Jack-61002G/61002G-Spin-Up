#include "globals.h"
#include "main.h"
using namespace okapi;

//profiler->setTarget(-6_ft);
//profiler->waitUntilSettled();

void autonomous() {

    // Chassis' max velocity, acceleration, and jerk
    ProfileConstraint moveLimit({5.3_ftps, 6_ftps2, 27_ftps3});

    //FFVelocityController leftController(0.23, .025, .01, 1.8, .1);
    //FFVelocityController rightController(0.23, .025, .01, 1.8, .1);


    std::shared_ptr<AsyncMotionProfiler> profiler =
    AsyncMotionProfilerBuilder()
        .withOutput(chassis)
        .withProfiler(std::make_unique<SCurveMotionProfile>(moveLimit))
        //.withLinearController(leftController, rightController)
        .build();

    profiler->setTarget(6_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-6_ft);
    profiler->waitUntilSettled();
    /*
    //intake on
    profiler->setTarget(4_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-90_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(1.5_ft);
    profiler->waitUntilSettled();
    //intake off
    profiler->setTarget(-1.5_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(90_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(-4_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(45_deg);
    pros::delay(1000);
    //adjust and shoot
    profiler->setTarget(-48_deg);
    profiler->waitUntilSettled();
    //intake on
    profiler->setTarget(8.2_ft);
    profiler->waitUntilSettled();
    //intake off
    profiler->setTarget(135_deg);
    profiler->waitUntilSettled();
    //adjust and shoot
    profiler->setTarget(-16_deg);
    profiler->waitUntilSettled();
    //intake on
    profiler->setTarget(4_ft);
    profiler->waitUntilSettled();
    //intake off
    profiler->setTarget(-4_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(16_deg);
    profiler->waitUntilSettled();
    //spin roller
    profiler->setTarget(-61_deg);
    profiler->waitUntilSettled();
    //intake on
    profiler->setTarget(2_ft);
    profiler->waitUntilSettled();
    //intake off
    profiler->setTarget(-2_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-55_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(2_ft);
    profiler->waitUntilSettled();
    //spin roller
    profiler->setTarget(-6_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(11_deg);
    profiler->waitUntilSettled();
    //adjust and shoot
    profiler->setTarget(-66_deg);
    profiler->waitUntilSettled();
    //intake on
    profiler->setTarget(-79_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(1.5_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-55_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(4_ft);
    profiler->waitUntilSettled();
    //intake off
    profiler->setTarget(100_deg);
    profiler->waitUntilSettled();
    //shoot
    profiler->setTarget(70_deg);
    profiler->waitUntilSettled();
    //intake on
    profiler->setTarget(5.5_ft);
    profiler->waitUntilSettled();
    //intake off
    profiler->setTarget(-30_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(3_ft);
    profiler->waitUntilSettled();
    //turn roller
    profiler->setTarget(-3_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(30_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(-5.5_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-70_deg);
    profiler->waitUntilSettled();
    //shoot
    profiler->setTarget(35_deg);
    profiler->waitUntilSettled();
    //intake on
    profiler->setTarget(3.5_ft);
    profiler->waitUntilSettled();
    //intake off
    profiler->setTarget(-3.5_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-35_deg);
    profiler->waitUntilSettled();
    //shoot
    profiler->setTarget(60_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(2.75_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-15_deg);
    profiler->waitUntilSettled();
    //intake on
    profiler->setTarget(6_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-45_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(1.5_ft);
    profiler->waitUntilSettled();
    //intake off
    profiler->setTarget(-90_deg);
    profiler->waitUntilSettled();
    //shoot em up
    profiler->setTarget(-13_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(1.5_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-32_deg);
    profiler->waitUntilSettled();
    //intake on
    profiler->setTarget(5_ft);
    profiler->waitUntilSettled();
    //intake off
    */
}