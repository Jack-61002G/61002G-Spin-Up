#pragma once
#include "TaskWrapper.hpp"
#include "lemlib/pose.hpp"

class Catapult : public ryan::TaskWrapper{

private:

  bool cata_override = false;
  bool state = false;
  bool useAltLimitSwitch = false;

public:

    void fire();

    void loop() override;

    bool getState();

    void fire(lemlib::Pose pose);
    };
