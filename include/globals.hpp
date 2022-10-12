#include "okapi/impl/device/motor/motorGroup.hpp"
#include "pros/adi.hpp"
#include "pros/motors.hpp"
#include "ryanlib/api.hpp"

extern bool flywheel_state;
extern pros::Motor catapultMotor;
extern pros::ADIButton limitButton;
extern pros::Controller master;


extern void cataTask();

// odom
extern double head;
extern int degrees;
extern double posX, posY;
extern bool odom_state;

extern std::shared_ptr<okapi::ChassisController> chassis;
extern std::shared_ptr<AsyncMotionProfiler> profiler;