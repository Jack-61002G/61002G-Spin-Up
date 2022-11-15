#include "globals.h"

class Catapult {

    bool cataState = false;

    public: int doCata() { // true - turn motor    false - stop motor
    
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)){
            return true;
            cataState = false;

        } else if ((limitButton.get_value() == false) && (cataState == false)) { 
            //move catapult down until its reached loading position
            return true;
            cataState = false;
        } else {
            return false;
            cataState = true;
        }
    }

};