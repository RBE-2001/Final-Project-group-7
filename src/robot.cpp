#include "robot.h"

void Robot::InitializeRobot(void)
{
    Serial.println("Robot initialized.");

    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
}

void Robot::EnterIdleState(void)
{
    Serial.println("-> IDLE");
}

Romi32U4ButtonA buttonA;
Romi32U4ButtonB buttonB;

/**
 * The main loop for your robot. Process both synchronous events (motor control),
 * and asynchronous events (distance readings, etc.).
*/
void Robot::RobotLoop(void) 
{

}