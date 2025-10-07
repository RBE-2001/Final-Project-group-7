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

// for debugging
long newPosition1 = 0;
long newPosition2 = 0;


int steps = 0;
int lastStep = -1; 

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

    // entering states
    if (steps != lastStep) {
      lastStep = steps;
      switch (steps)
      {
        case 1:
          extender.ExtendCommand(); break;
        case 2:
          gripper.CloseCommand(); break;
        case 3:
          extender.RetractCommand(); break;
        case 4:
          lifter.L25Command(); break;
        default:
          steps = 0; break;
      }
    }

    // all done ready for next state
    bool done = extender.IsDone();
    done = done && gripper.IsDone();
    done = done && lifter.IsDone();
    if (done){
      steps ++;
      done = false;
    }

}