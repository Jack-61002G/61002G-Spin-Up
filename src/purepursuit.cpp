#include "main.h"
#include "globals.h"
#include <cmath>

class robotMovement { 

    void goToPosition(double x, double y, double movementSpeed) {
        double absoluteAngleToTarget = atan2(y-posY, x-posX);

        double realativeAngleToPoint = angleWrap(absoluteAngleToTarget - head);


        double relativeXToPoint = cos(realativeAngleToPoint);
    }

    double angleWrap(double angle) { // makes sure the angle is between 180, -180
        while (angle < -M_PI) {
            angle += 2 * M_PI;
        }
        while (angle > M_PI) {
            angle -= 2 * M_PI;
        }
        return angle;
    }
};