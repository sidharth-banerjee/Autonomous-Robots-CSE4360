#include <ev3.h>
#include <string>
#include "sensor.h"
#include "behavior.h"
#include "control.h"
int GoalReached = 0;
int extNextRoom = 200;
int extMaxLeftTurn = 8;
int extSightCount = 5;
int SPEED = 25;
int extMoveBack = 10;
int extUnitLength = 305;
int extRightAngleTurn = 87;
int RIGHTMAXDISTANCE = 50;
void goal_reached()
{
  stop();
  GoalReached =1;
  extmoveForward = 0;
  LightGoalFlag = 1;
  std::string greeting("Goal Reached!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  SetLedPattern(LED_GREEN_PULSE);
  //Wait(1000);
}
void follow_wall(){
  int leftturn = 0;
  int rightturn = 0;
  int checklineofsight = 0;
  SetLedPattern(LED_ORANGE_PULSE);
  if(GoalReached ==1 || extLineOfsight == 1){
    stop();
  }
  move_forward(extUnitLength*15,SPEED);
  if(GoalReached ==0 || extLineOfsight == 0){
    turn_anticlockwise(extRightAngleTurn);
  }
  //stop();
  for(int index =0;index<25;index++){
    SetLedPattern(LED_ORANGE_PULSE);
    if(GoalReached ==1 || extLineOfsight == 1){
      stop();
      break;
    }
    move_forward(extUnitLength*1,SPEED);
    checklineofsight++;
    if(checklineofsight >= extSightCount){ // search for candle
      if(GoalReached ==1 || extLineOfsight == 1){
        stop();
        break;
      }
      move_backward(extMoveBack,SPEED);
      turn_anticlockwise(360);
      checklineofsight = 0;
    }
    //CheckLineofSite();
    if(extmoveForward == 0){
      if(leftturn < extMaxLeftTurn){
        if(GoalReached ==1 || extLineOfsight == 1){
          stop();
          break;
        }
        move_backward(extMoveBack,SPEED);//reverse to deal with unknown stuck
        if(GoalReached ==1 || extLineOfsight == 1){
          stop();
          break;
        }
        turn_anticlockwise(extRightAngleTurn);
        leftturn++;
      }
      else{//stuck in loop door must be on right side
        //check for door if door found enter another room
        if(extrightSonarSensor > extNextRoom){
          if(GoalReached ==1 || extLineOfsight == 1){
            stop();
            break;
          }
          move_backward(extMoveBack,SPEED);//reverse to deal with unknown stuck
          if(GoalReached ==1 || extLineOfsight == 1){
            stop();
            break;
          }
          turn_clockwise(extRightAngleTurn);
          //try to reach wall of new room
          if(GoalReached ==1 || extLineOfsight == 1){
            stop();
            break;
          }
          //move_forward(5,SPEED);//clearlenrace buffer
          if(rightturn>5){
            leftturn = 0;
            rightturn =0;
          }
          else{
            rightturn++;
          }
          //break;//stop and switch to explore mode after entering into new room
          //rightturn = 0;
        }
        else{
          turn_anticlockwise(extRightAngleTurn);
          leftturn++;
        }
      }
    }
    else if(extrightSonarSensor >RIGHTMAXDISTANCE && extrightSonarSensor <200 ){
      //drift towards left rotate to its right
      if(GoalReached ==1 || extLineOfsight == 1){
        stop();
        break;
      }
      turn_clockwise(5);
    }
    else{
      //leftturn =0;
    }
    if(extrightSonarSensor > extNextRoom){
      //found door for another room
      if(GoalReached ==1 || extLineOfsight == 1){
        stop();
        break;
      }
      move_backward(5,10);//reverse to deal with unknown stuck
      turn_clockwise(extRightAngleTurn);
      if(GoalReached ==1 || extLineOfsight == 1){
        stop();
      }
      //move_forward(25,SPEED);
      /*
      if(GoalReached ==1 || extLineOfsight == 1){
      stop();
      break;
    }
    if(leftturn >extMaxLeftTurn){
    move_backward(5,10);//reverse to deal with unknown stuck
    turn_clockwise(90);
    if(GoalReached ==1 || extLineOfsight == 1){
    stop();
    break;
  }
  move_forward(extUnitLength*2,10);
  leftturn =0;
  break;
}
else{
leftturn++;
}
if(GoalReached ==1 || extLineOfsight == 1){
stop();
break;
}
*/
//CheckLineofSite();
//break;
}
}
}
void wander(){
  int turndirection;
  SetLedPattern(LED_RED_PULSE);
  for(int index=0;index<10;index++)
  {
    SetLedPattern(LED_RED_PULSE);
    if(GoalReached ==1 || extLineOfsight == 1){
      break;
    }
    turndirection = rand() %3;
    if(turndirection == 0){
      move_backward(extMoveBack,SPEED);//reverse to deal with unknown stuck
      if(GoalReached ==1 || extLineOfsight == 1){
        break;
      }
      turn_clockwise(extRightAngleTurn);
    }
    else if(turndirection == 1){
      move_backward(extMoveBack,SPEED);//reverse to deal with unknown stuck
      if(GoalReached ==1 || extLineOfsight == 1){
        break;
      }
      turn_anticlockwise(extRightAngleTurn);
    }
    else{
      if(GoalReached ==1 || extLineOfsight == 1){
        break;
      }
      int move_length = rand() %2+1;
      move_forward(extUnitLength*move_length,SPEED);
    }
    if(GoalReached ==1 || extLineOfsight == 1){
      break;
    }
    move_forward(extUnitLength*1,SPEED);
    CheckLineofSite();
  }
}
void CheckLineofSite(){
  int turndirection;
  if(extSightCount == 1){
    move_backward(extMoveBack,SPEED);
    turn_clockwise(360);
  }
  turndirection = rand() %2;
  if(turndirection == 0){
    move_backward(extMoveBack,SPEED);
    turn_clockwise(360);
  }
  else{
    move_backward(extMoveBack,SPEED);
    turn_anticlockwise(360);
  }
}
void ext_fire(){
  stop();
  RotateFan();
  stop();
  turn_clockwise(45);
  stop();
  RotateFan();
  stop();
  turn_anticlockwise(90);
  stop();
  RotateFan();
  stop();
}
#endif
