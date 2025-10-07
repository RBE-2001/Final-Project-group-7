#include "robot.h"

void Robot::InitializeRobot(void)
{
    // chassis.Init();
    extender.Init();
    gripper.Init();
    lifter.Init();
    
    Serial.println("Robot initialized.");

  motor1.setup();
  motor1.reset();
  
  motor2.setup();
  motor2.reset();
}

Romi32U4ButtonA buttonA;
Romi32U4ButtonB buttonB;

long newPosition1 = 0;
long newPosition2 = 0;

/**
 * The main loop for your robot. Process both synchronous events (motor control),
 * and asynchronous events (distance readings, etc.).
*/
void Robot::RobotLoop(void) 
{
    // chassis.Update();
    extender.Update();
    gripper.Update();
    lifter.Update();

    if (buttonA.getSingleDebouncedPress()) {
        //delay(250); //wait so you can move your finger
        extender.ExtendCommand();
        // lifter.L3Command();
    }
    if (buttonB.getSingleDebouncedPress()) {
        //delay(250); //wait so you can move your finger
        extender.RetractCommand();
        // lifter.L1Command();
    }
    // motor1.setEffort(350);
    // motor2.setEffort(350);
    
    newPosition1 = motor1.getPosition();
    newPosition2 = motor2.getPosition();

    Serial.print(newPosition1);
    Serial.print("          ");
    Serial.print(newPosition2);
    Serial.println("");
}