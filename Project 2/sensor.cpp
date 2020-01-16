/*
* sensor.cpp
*
* Created on: Nov 20, 2019
* Author: Team_5
*/
#include<string>
#include "sensor.h"
#include"control.h"
#include "behavior.h"
int TRANSPARENT = 0;
int BLACK = 1;
int BLUE = 2;
int GREEN = 3;
int YELLOW = 4;
int RED = 5;
int WHITE = 7;
int BROWN = 8;
int FRONTSAFEDISTANCE = 60;
int RIGHTSAFEDISTANCE = 35;
int LIGHTTHRESHOLD = 22;
int extLineOfsight = 0;
int extmoveForward = 1;
int extmoveRight = 1;
int extlightSensor = -1;
int extcolorSensor = -1;
int extfrontSonarSensor = -1;
int extrightSonarSensor = -1;
int extSightFlag = 1;
int LightGoalFlag = 0;
int extLightGoalCount = 0;
int GoalLightThreashold = 35;
int setSensor(){
  //IN_1 = front sonar
  //IN_2 = light sensor
  //IN_3 = color sensor
  //IN_4 = Right sonar
  return setAllSensorMode(COL_AMBIENT,US_DIST_MM,COL_COLOR,US_DIST_MM);
}
void ReadLightSensor(){
  char buffer[5];
  std::string greeting("light sr rd init!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  while(true){
    extlightSensor = readSensor(IN_1);
    //line of sight call front moving
    if(extlightSensor > LIGHTTHRESHOLD)
    {
      //line of sight
      extLineOfsight = 1;
      if(GoalReached ==0 ){
        SetLedPattern(LED_RED);
      }
      if(extSightFlag == 1){
        stop();
        extSightFlag = 0;
      }
      //sprintf(buffer, "light = %d ,", extlightSensor);
      //LcdPrintf(1,buffer);
      //Wait(1000);
    }
    //keep buffer to handle wrong reading randomly
    else if(extlightSensor < (LIGHTTHRESHOLD -5))
    {
      extSightFlag = 1;
      extLineOfsight = 0;
      sightflag = 1;
    }
    if(extlightSensor > GoalLightThreashold){
      move_forward(170,10);
      if(extLightGoalCount > 20){
        LightGoalFlag = 1;
        goal_reached();
      }
      else{
        extLightGoalCount++;
      }
    }
    else{
      extLightGoalCount = 0;
      LightGoalFlag = 0;
    }
    if(!ButtonIsUp(BTNUP))
    {
      FreeEV3();
    }
  }
}
void ReadColorSensor(){
  char buffer[5];
  std::string greeting("color sr rd init!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  while(true){
    extcolorSensor = readSensor(IN_3);
    //call stop and announced reached goal after goal color code
    if(extcolorSensor == RED)
    {
      goal_reached();
      //sprintf(buffer, "col = %d\n", extcolorSensor);
      //LcdPrintf(1,buffer);
      //Wait(1000);
      break;
    }
  }
}
void ReadFrontSonar(){
  char buffer[5];
  std::string greeting("Fnt sr rd init!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  while(true){
    extfrontSonarSensor = readSensor(IN_2);
    //sprintf(buffer, "frt so = %d\n", front_distance);
    //LcdPrintf(1,buffer);
    //Wait(1000);
    if(extfrontSonarSensor < FRONTSAFEDISTANCE)
    {
      //after rotation in control.cpp stopflag set to 1
      if(extmoveForward == 1){
        extmoveForward = 0;
        //front sensor warning
        SetLedPattern(LED_ORANGE_FLASH);
        stop();
      }
    }
    else{
      extmoveForward = 1;
    }
  }
  //after close approximity call stop
}
void ReadRightSonar(){
  char buffer[5];
  std::string greeting("Rgt sr rd init!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  while(true){
    extrightSonarSensor = readSensor(IN_4);
    //after close approximity call stop
    //sprintf(buffer, "rgt so = %d ,", extrightSonarSensor);
    //LcdPrintf(1,buffer);
    //Wait(1000);
    if(extrightSonarSensor < RIGHTSAFEDISTANCE)
    {
      if(extmoveRight == 1){
        extmoveRight = 0;
        //right sendor warning
        SetLedPattern(LED_RED_FLASH);
      }
    }
    else{
      extmoveRight = 1;
    }
  }
}
