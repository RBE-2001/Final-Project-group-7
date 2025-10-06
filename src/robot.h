#pragma once

#include "Romi32U4Buttons.h"

class Robot
{
protected:
    // For managing key presses
    String keyString;

public:
    Robot(void) {keyString.reserve(10);}
    void InitializeRobot(void);
    void RobotLoop(void);

protected:
    /* State changes */    
    void EnterIdleState(void);
};
