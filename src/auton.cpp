#include "globals.hpp"
#include "main.h"

//profiler->setTarget(-6_ft);
//profiler->waitUntilSettled();

void autonomous() {

    //intake active
    profiler->setTarget(6_ft);
    profiler->waitUntilSettled();
    profiler->setTarget(-90_deg);
    profiler->waitUntilSettled();

}