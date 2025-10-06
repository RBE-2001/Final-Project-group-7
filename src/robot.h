#pragma once

#include "Romi32U4Buttons.h"

#include "subsystems/ChassisSubsystem.h"
#include "subsystems/ExtenderSubsystem.h"
#include "subsystems/GripperSubsystem.h"
#include "subsystems/LifterSubsystem.h"

#include "DualBlueMotor.h"

class Robot
{
protected:
    // For managing key presses
    String keyString;

    // // Constructor: pwm pin, motor pins + encoder pins
    // DualBlueMotor(int pwmPin,
    //                     int m1_ain1, int m1_ain2, int m1_encA, int m1_encB,
    //                     int m2_ain1, int m2_ain2, int m2_encA, int m2_encB);
    DualBlueMotor dualMotor = DualBlueMotor(11, 1, 2, 3, 4, 5, 6, 7 ,8);
    // Subsytems
    ChassisSubsystem chassis;
    ExtenderSubsystem extender = extender(dualMotor);
    GripperSubsystem gripper;
    LifterSubsystem lifter = lifter(dualMotor);

public:
    Robot(void) {keyString.reserve(10);}
    void InitializeRobot(void);
    void RobotLoop(void);
};
