#include <ev3.h>
#include <string>
#include "sensor.h"
#include "behavior.h"
#include "control.h"
int extOpponetArea = 0;
int extOpponentColor = -1;
int extRedColor = 5;
int extGreenColor = 3;;
int extBlackColor = 1;
int extDetectBall = 0;
void FollowBall(){
  MoveTowardsBall();
}
void PushGoal(){
  PushToGoal();
}
void Explore(){
  ControlExplore();
}
void OpponentDefence(){
  //color code depent upon opponet
  while(true){
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
      break;
    }
    if(extColorSensor == extGreenColor || extColorSensor == extRedColor){
      extOpponetArea = 1;
    }
    else{
      extOpponetArea = 0;
    }
  }
}
void DetectBall(){
  while(true){
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
      break;
    }
    if(extTouchSensor >= 4 && extTouchSensor <=6){
      extDetectBall = 1;
    }
    else{
      extDetectBall = 0;
    }
  }
}
void Retreat(){
  ExecuteRetreat();
}
