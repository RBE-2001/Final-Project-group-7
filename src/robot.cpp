#include "robot.h"

Romi32U4ButtonA buttonA;
Romi32U4ButtonB buttonB;

void Robot::InitializeRobot(void)
{
    chassis.Init();
    extender.Init();
    gripper.Init();
    lifter.Init();
    
    Serial.println("Robot initialized.");

    motor1.setup();
    motor1.reset();
    
    motor2.setup();
    motor2.reset();
//   while(!buttonB.getSingleDebouncedPress()){delay(5);}
}


// for debugging
long newPosition1 = 0;
long newPosition2 = 0;


int steps = 0;
int lastStep = -1; 

bool start = false;

/*

TODO List
1. Remove as muuch friction in system as posile
- extender, large gear, shorter olts, resess bolts
2. test extender, get it goung back and forth
3. test up and down, get it gong to min and max
- check motors are spining right derection
- have it drive up and down, no pid
- drive motors two set points, not mounted
4. gripper
- make this shit work
5. run all systems in order
6. tune evrything, proaly want second between swiching
 */

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

    if (buttonA.getSingleDebouncedPress()) {
        //delay(250); //wait so you can move your finger
        // extender.ExtendCommand();
        // // lifter.L3Command();
        // gripper.CloseCommand();
        start = true;
        // Serial.println("Button A");
        // steps += 1;
    }
    if (buttonB.getSingleDebouncedPress()) {
        //delay(250); //wait so you can move your finger
        // extender.RetractCommand();
        // gripper.OpenCommand();
        // lifter.L1Command();
        // chassis.SetDestinationCommand();
    }
    // motor1.setEffort(350);
    // motor2.setEffort(350);
    newPosition1 = motor1.getPosition();
    newPosition2 = motor2.getPosition();

    // Serial.print(newPosition1);
    // Serial.print("          ");
    // Serial.print(newPosition2);
    // Serial.println("");
    // if (steps != lastStep) {
    //     lastStep = steps;
    //     switch (steps)
    //     {
    //         case 1:
    //             lifter.L1Command(); break;
    //         case 2:
    //             lifter.L15Command(); break;
    //         case 3:
    //             lifter.L2Command(); break;
    //         case 4:
    //             lifter.L25Command(); break;
    //         case 5:
    //             lifter.L3Command(); break;
    //         default:
    //             steps = 0; break;
    //     }
    // }
    //entering states
    if (steps != lastStep) {
      lastStep = steps;
      switch (steps)
      {
        case 1:
            extender.ExtendCommand(); break;
        case 2:
            gripper.CloseCommand(); break;
        case 3:
            lifter.L15Command(); break;
        case 4:
            extender.RetractCommand(); break;
        case 5:
            lifter.L25Command(); break;
        case 6:
            extender.ExtendCommand(); break;
        case 7:
            lifter.L2Command(); break;
        case 8:
            gripper.OpenCommand(); break;
        case 9:
            lifter.L25Command(); break;
        case 10:
            extender.RetractCommand(); break;
        case 11:
            lifter.L3Command();  break;
        case 12:
            extender.ExtendCommand(); break;
        case 13:
            gripper.CloseCommand(); break;
        case 14:
            extender.RetractCommand(); break;
        case 15:
            lifter.L15Command(); break;
        case 16:
            gripper.OpenCommand(); break;
        default:
          steps = 0; break;
      }
    }

    // // // all done ready for next state
    bool done = extender.IsDone();
    done = done && gripper.IsDone();
    done = done && lifter.IsDone();
    done = done && start;
    if (done){
      steps ++;
      delay(1000);
    }

}