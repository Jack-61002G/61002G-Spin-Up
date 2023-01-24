#include "main.h"
#include "pros/adi.hpp"
#include "pros/misc.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

pros::Controller master(pros::E_CONTROLLER_MASTER);
pros::Motor catapultMotor(19, pros::E_MOTOR_GEARSET_36, true);
pros::ADIButton limitButton('A');
pros::Motor intake1(9);
int intakeState = 0;

void cataTask();
void intaketoggle();
bool cata_override = false;

/*void cata_task_fn() {
  
  bool cataState = false;

  while (true) {

    if (cata_override) {
      cataState = false;
      catapultMotor = 127;
      pros::delay(300);
      cata_override = false;

    } else if ((limitButton.get_value() == false) && (cataState == false)) {
      // move catapult down until its reached loading position
      catapultMotor = 127;

    } else {
      cataState = true;
      catapultMotor = 0;
    }

    pros::delay(20);
  }
}*/

class Catapult {
private:
  bool cata_override = false;

public:
  Catapult() {
    pros::Task cata_task = pros::Task([this]() {
      bool cataState = false;
      while (true) {
        if (cata_override) {
          cataState = false;
          catapultMotor = 127;
          pros::delay(300);
          cata_override = false;
        } else if ((limitButton.get_value() == false) && (cataState == false)) {
          // move catapult down until its reached loading position
          catapultMotor = 127;
        } else {
          cataState = true;
          catapultMotor = 0;
        }
        pros::delay(20);
      }
    });
  }

  void fire() {
    cata_override = true;
  }
};




