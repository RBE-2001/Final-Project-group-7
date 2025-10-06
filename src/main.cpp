#include <Arduino.h>
#include "robot.h"

Robot robot;

void setup() 
{
  Serial.begin(115200);

#ifdef __SETUP_DEBUG__
  while(!Serial){delay(5);}
#endif

  robot.InitializeRobot();
}

void loop() 
{
  robot.RobotLoop();
}
