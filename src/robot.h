#pragma once

#include "Romi32U4Buttons.h"

// #include "subsystems/ChassisSubsystem.h"
#include "subsystems/ExtenderSubsystem.h"
#include "subsystems/GripperSubsystem.h"
#include "subsystems/LifterSubsystem.h"

#include "BlueMotorLifter.h"
#include "BlueMotorExtender.h"

class Robot
{
protected:
    // For managing key presses
    String keyString;

    // // Constructor: pwm pin, motor pins + encoder pins
    // DualBlueMotor(int pwmPin,
    //                     int m1_ain1, int m1_ain2, int m1_encA, int m1_encB,
    //                     int m2_ain1, int m2_ain2, int m2_encA, int m2_encB);
    // Motor 1 pins ain1=4 ain2=13 encA=0, encB=1
    // Motor 2 pins bin1=20 bin2=21 encA=2, encB=3

    BlueMotorLifter motor1;
    BlueMotorExtender motor2;
    // Subsytems
    // ChassisSubsystem chassis;
    ExtenderSubsystem extender;
    GripperSubsystem gripper;
    LifterSubsystem lifter;

public:
    Robot(void) {keyString.reserve(10);}
    void InitializeRobot(void);
    void RobotLoop(void);
};
