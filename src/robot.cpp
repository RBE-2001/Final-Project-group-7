#include "robot.h"

void Robot::InitializeRobot(void)
{
    chassis.Init();
    extender.Init();
    gripper.Init();
    lifter.Init();

    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    
    Serial.println("Robot initialized.");
}

Romi32U4ButtonA buttonA;
Romi32U4ButtonB buttonB;

/**
 * The main loop for your robot. Process both synchronous events (motor control),
 * and asynchronous events (distance readings, etc.).
*/
void Robot::RobotLoop(void) 
{
    chassis.Update();
    extender.Update();
    gripper.Update();
    lifter.Update();
}