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



    //intake active
    profiler->setTarget(6_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-90_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(0.75_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-0.75_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(90_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(-6_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(45_deg);
    //adjust distance
    //shoot discs
    profiler->setTarget(-12_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(4.6_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-2_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(57_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(2_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-2_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(60_deg);
    profiler->waitUntilSettled();
    profiler->setTarget(1_ft);


}