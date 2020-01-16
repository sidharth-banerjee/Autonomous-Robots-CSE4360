//============================================================================
#include <ev3.h>
#include<iostream>
#include <string>
#include<thread>
#include"sensor.h"
#include"control.h"
#include"behavior.h"
int goalmovecoutn = 0;
int main()
{
  InitEV3();
  std::string greeting("proj 2 started!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  int initsensor = setSensor();
  std::thread colorthread(ReadColorSensor);
  std::thread lightthread(ReadLightSensor);
  std::thread frontsonarthread(ReadFrontSonar);
  std::thread rightsonarthread(ReadRightSonar);
  /*
  turn_clockwise(90);
  stop();
  Wait(2000);
  turn_anticlockwise(90);
  stop();
  Wait(2000);*/
  while(true)
  {
    //don't comment it
    if(GoalReached ==1){
      //blow the candle action
      SetLedPattern(LED_GREEN_PULSE);
      ext_fire();
      stop();
      break;
    }
    if(extLineOfsight == 1){
      SetLedPattern(LED_RED);
      //extSightCount = 0;
      /*
      std::string greeting("line of sight!");
      LcdPrintf(1, "%s\n", greeting.c_str());
      Wait(2000);
      */
      //extSightFlag = 0;
      move_forward(305,40);
      while(extLineOfsight == 1){
        turn_clockwise(10);
        move_forward(30,10);
        turn_anticlockwise(20);
        move_forward(30,10);
      }
      /*
      if(goalmovecoutn < 6)
      {
      //move_backward(3,10);
      //stop();
      //Wait(2);
      goalmovecoutn++;
    }
    else{
    move_backward(15,20);
    goalmovecoutn = goalmovecoutn - 2;
    turn_clockwise(30);
    if((extLineOfsight == 1)){
    move_backward(30,10);
    move_forward(305*1,40);
  }
  else{
  turn_anticlockwise(60);
  move_backward(30,20);
  move_forward(305*1,40);
}
if((extLineOfsight != 1)){
turn_anticlockwise(360);
}
//turn_anticlockwise(360);
}
*/
continue;
}
goalmovecoutn=0;
extLineOfsight=0;
if(GoalReached == 0 && extLineOfsight == 0){
  follow_wall();
  wander();
}
if(!ButtonIsUp(BTNUP))
{
  FreeEV3();
}
}
while(true){
  if(GoalReached ==1){
    //blow the candle action
    SetLedPattern(LED_GREEN_PULSE);
    stop();
  }
  if(!ButtonIsUp(BTNUP))
  {
    FreeEV3();
  }
}
colorthread.join();
lightthread.join();
frontsonarthread.join();
rightsonarthread.join();
Wait(2000);
FreeEV3();
}
