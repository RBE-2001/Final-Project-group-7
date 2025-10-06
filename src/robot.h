#pragma once

#include "Romi32U4Buttons.h"

#include "subsystems/ChassisSubsystem.h"
#include "subsystems/ExtenderSubsystem.h"
#include "subsystems/GripperSubsystem.h"
#include "subsystems/LifterSubsystem.h"

class Robot
{
protected:
    // For managing key presses
    String keyString;

    // Subsytems
    ChassisSubsystem chassis;
    ExtenderSubsystem extender;
    GripperSubsystem gripper;
    LifterSubsystem lifter;

public:
    Robot(void) {keyString.reserve(10);}
    void InitializeRobot(void);
    void RobotLoop(void);
};
