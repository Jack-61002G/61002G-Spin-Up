#include "globals.hpp"
#include "main.h"
#include <tuple>

void real_Odometry() {
#define center 5         // distance between side wheels
#define back_to_center 0 // yes
  int oldR{0}, oldL{0}, oldB{0}, R, L, B;
  const double cst{M_PI * 2.75 / 360}; // inches per encoder tick
  double dX, dY, dH, dR, dL, dB;

  pros::ADIEncoder left('A', 'B', true);
  pros::ADIEncoder right('G', 'H');
  pros::ADIEncoder back('C', 'D', true);
  while (true) {
    R = right.get_value();
    L = left.get_value();
    B = back.get_value();

    dR = R - oldR;
    dL = L - oldL; // getting the change in degrees from the last cycle
    dB = B - oldB;

    dX = cst * (dB - back_to_center * ((dR + dL) / center));
    dY = cst * ((dR + dL) / 2); // calculate change in x, y, and heading
    dH = cst * ((dR - dL) / center);

    head += dH;
    degrees = head * 180 / M_PI; // add the change in heading to the global
                                 // heading, and then convert to degrees

    posX += (dX * cos(head)) - (dY * sin(head));
    posY += (dX * sin(head)) + dY * (cos(head));
    // add the change in x and y to the global position

    oldR = R;
    oldL = L; // update old encoder values
    oldB = B;

    pros::delay(10);
    
  }
}