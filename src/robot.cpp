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
long timeToPrint = 0;
long now = 0;
long newPosition = 0;
long oldPosition = 0;
long sampleTime = 100;
int speedInRPM = 0;
int CPR = 270;
int motorEffort = 400;

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

    // if (buttonA.getSingleDebouncedPress()) {
    //     delay(250); //wait so you can move your finger
    //     extender.ExtendCommand();
    // }

    motor1.setEffort(300);
    motor1.setEffort(100);
    if ((now = millis()) > timeToPrint)
    {
      timeToPrint = now + sampleTime;
      newPosition = motor1.getPosition();
      speedInRPM = (newPosition - oldPosition)/1080 * (60000 / sampleTime);
      Serial.print(now);
      Serial.print("          ");
      Serial.print(newPosition);
      Serial.print("          ");
      Serial.println(speedInRPM);
      oldPosition = newPosition;
      
    }
}