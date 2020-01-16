/*
* control.cpp
*
* Created on: Nov 20, 2019
* Author: Team_5
*/
#include <ev3.h>
#include<cmath>
#include <string>
#include"control.h"
#include "sensor.h"
#include"behavior.h"
int extMoveLength = 0;
int extSwitchtoFollow = 0;
void move_forward(int length,int speed,int sync,int Retreat,int push){
  ResetRotationCount(OUT_ABCD);
  char buffer[15];
  char vbuffer[15];
  long c = 176; // circumference of wheel in mm
  double motor_rot = (length * 360)/c;
  motor_rot = motor_rot/3;
  int count = 0;
  //motor_rot = motor_rot*5.0;
  while(-1*MotorRotationCount(OUT_D)<motor_rot)
  {
    //count++;
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
    }
    if(1 == extOpponetArea){
      ExecuteRetreat();
      break;
    }
    if( 1 == extDetectBall && 0 == push){
      PushToGoal();
      break;
    }
    if(extInraRedSensor>0 && extInraRedSensor<=9){
      extSwitchtoFollow = 1;
      if( 0 == Retreat){
        break;
      }
    }
    /*
    sprintf(buffer, "mf = %d\n,", extfrontSonarSensor);
    LcdPrintf(1,buffer);
    Wait(2000);
    sprintf(vbuffer, "mr = %d\n,", extrightSonarSensor);
    LcdPrintf(1,vbuffer);
    Wait(2000);
    */
    //OnRevSync(OUT_AD, speed);
    if(0 == sync){
      OnRevReg(OUT_A, speed);
      OnRevReg(OUT_D, speed-45);
    }
    else if(1 == sync){
      OnRevSync(OUT_AD, speed);
    }
    //OnRevReg(OUT_D, speed);
  }
  stop();
}
void move_backward(int length,int speed,int Retreat){
  ResetRotationCount(OUT_ABCD);
  long c = 176; // circumference of wheel in mm
  double motor_rot = (length * 360)/c;
  double remaining_motor_cnt = motor_rot;
  motor_rot = motor_rot/3;
  //motor_rot = motor_rot*5.0;
  while(MotorRotationCount(OUT_D)<motor_rot)
  {
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
    }
    if(extInraRedSensor>0 &&extInraRedSensor<=9){
      extSwitchtoFollow = 1;
      if( 0 == Retreat){
        break;
      }
    }
    if(0 == Retreat){
      if(1 == extOpponetArea){
        //stop();
        //move_forward(225,50);
        for(int index = 0;index < 500;index++){
          OnRevSync(OUT_AD, 100);
          //break;
        }
        break;
      }
    }
    //OnRevSync(OUT_AD, speed);
    OnFwdSync(OUT_AD, speed);
  }
  stop();
}
void turn_clockwise(int theta,int GyroFlg,int Retreat){
  //move_backward(5,10);
  ResetRotationCount(OUT_ABCD);
  //speed = 8; // change this to turn at different speed
  long R = 150/2; // in mm
  long c = 176; // circumference of wheel in mm
  double motor_rot =( R * theta * M_PI * 360)/ (180 * c);
  motor_rot = motor_rot/3;
  while(-1*MotorRotationCount(OUT_A) < motor_rot){
    if(1 == extOpponetArea){
      ExecuteRetreat();
      break;
    }
    if( 1 == extDetectBall ){
      PushToGoal();
      break;
    }
    if(extInraRedSensor>0 &&extInraRedSensor<=9){
      extSwitchtoFollow = 1;
      if( 0 == Retreat){
        break;
      }
    }
    OnRevReg(OUT_A, 50);
    OnFwdReg(OUT_D, 50);
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
    }
  }
  stop();
}
void turn_anticlockwise(int theta,int GyroFlg,int Retreat){
  //move_backward(5,10);
  ResetRotationCount(OUT_ABCD);
  //speed = 8; // change this to turn at different speed
  long R = 140/2; // in mm
  long c = 176; // circumference of wheel in mm
  double motor_rot =( R * theta * M_PI * 360)/ (180 * c);
  motor_rot = motor_rot/3;
  while(MotorRotationCount(OUT_A) < motor_rot){
    if(1 == extOpponetArea){
      ExecuteRetreat();
      break;
    }
    if( 1 == extDetectBall ){
      PushToGoal();
      break;
    }
    if(extInraRedSensor>0 &&extInraRedSensor<=9){
      extSwitchtoFollow = 1;
      if( 0 == Retreat){
        break;
      }
    }
    OnRevReg(OUT_D, 50);
    OnFwdReg(OUT_A, 50);
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
    }
  }
  stop();
}
void MoveTowardsBall(){
  int searchcount = 0;
  int OldInfraRed = extInraRedSensor;
  SetLedPattern(LED_ORANGE_PULSE);
  if( 1 == extDetectBall ){
    PushToGoal();
  }
  if(1 == extOpponetArea){
    ExecuteRetreat();
  }
  while(true){
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
      break;
    }
    if( 1 == extDetectBall ){
      PushToGoal();
      break;
    }
    if(1 == extOpponetArea){
      ExecuteRetreat();
      break;
    }
    if(extInraRedSensor >0 && extInraRedSensor <=4){
      //front right wheel should go to D motor
      //front left wheel should go to A motor
      //left wheel motor A need extra power to rotate
      SetLedPattern(LED_ORANGE_PULSE);
      OnRevReg(OUT_D, 25); // Moving forward and turning anti clockwise
      OnRevReg(OUT_A, 7);
      OldInfraRed = extInraRedSensor;
      searchcount = 0;
    }
    else if(extInraRedSensor >5 && extInraRedSensor <=9){
      SetLedPattern(LED_ORANGE_PULSE);
      OnRevReg(OUT_D,3); // Moving forward and turning clockwise
      OnRevReg(OUT_A, 100);
      OldInfraRed = extInraRedSensor;
      searchcount =0;
    }
    else if(extInraRedSensor == 5){
      SetLedPattern(LED_ORANGE_PULSE);
      //OnRevSync(OUT_AD, 10);
      if(OldInfraRed >0 && OldInfraRed <=4){
        move_backward(10,50);
        turn_anticlockwise(45);
      }
      else if(OldInfraRed >5 && OldInfraRed <=9){
        move_backward(10,50);
        turn_clockwise(45);
      }
      OldInfraRed = extInraRedSensor;
      OnRevReg(OUT_D, 20); // Moving forward
      OnRevReg(OUT_A, 70);
      searchcount = 0;
    }
    else{
      if(OldInfraRed >0 && OldInfraRed <=4){
        SetLedPattern(LED_ORANGE_PULSE);
        move_backward(10,20);
        turn_anticlockwise(45);
        searchcount++;
      }
      else if(OldInfraRed >5 && OldInfraRed <=9){
        SetLedPattern(LED_ORANGE_PULSE);
        move_backward(10,20);
        turn_clockwise(45);
        searchcount++;
      }
      else{
      }
      if(searchcount == 5){
        break;
      }
      else{
        //turndirection = rand() %2;
        //if(turndirection == 0){
        //turn_anticlockwise(5);
        //}
        //else{
        //turn_clockwise(5);
        //}
        searchcount++;
      }
    }
  }
}
void stop()
{
  Off(OUT_ABCD);
}
/*
void PushToGoal()
{
char buffer[10];
sprintf(buffer, "Gf = %d\n,", extGyroSensor);
LcdPrintf(1,buffer);
Wait(2000);
sprintf(buffer, "IGf = %d\n,", extGyroInitReadingSensor);
LcdPrintf(1,buffer);
Wait(2000);
while(true)
{
if(!ButtonIsUp(BTNUP)){
FreeEV3();
break;
}
int init = extGyroInitReadingSensor%360;
int now = extGyroSensor % 360;
if(now - init < -180)
{
now = 360 + now;
}
else if (now - init > 180)
{
now = 360 - now;
}
//turn_anticlockwise
if (now < init-10)
{
//turn_clockwise(1.5);
//need clockwise rotation towards opponent
SetLedPattern(LED_GREEN_PULSE);
OnRevReg(OUT_A, 10); // Moving forward and turning clockwise
OnRevReg(OUT_D, 2);
}
else if (now > init+10)
{
//turn_anticlockwise(1.5);
//need anti clockwise rotation towards opponent
SetLedPattern(LED_RED_PULSE);
OnRevReg(OUT_D, 10); // Moving forward and turning anti clockwise
OnRevReg(OUT_A, 2);
}
else{
//stop();
//move_forward(50,30);
//SetLedPattern(LED_ORANGE_PULSE);
Wait(2000);
break;
}
}
}
*/
void PushToGoal()
{
  SetLedPattern(LED_GREEN_PULSE);
  extDetectBall = 0;
  /*
  char buffer[10];
  sprintf(buffer, "Gf = %d\n,", extGyroSensor);
  LcdPrintf(1,buffer);
  //Wait(2000);
  sprintf(buffer, "IGf = %d\n,", extGyroInitReadingSensor);
  LcdPrintf(1,buffer);
  //Wait(2000);
  */
  while(true)
  {
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
      break;
    }
    if(extOpponetArea == 1){
      ExecuteRetreat();
      break;
    }
    //int init = extGyroInitReadingSensor%360;
    //Making initial value logical zero
    //left wheel motor A need extra power to rotate Speed value is actually half of actual
    int currentGyro = extGyroSensor - extGyroInitReadingSensor;
    currentGyro = currentGyro %360;
    if( currentGyro >35 && currentGyro<=180){
      SetLedPattern(LED_GREEN_PULSE);
      OnRevReg(OUT_D, 35); // Moving forward and turning anti clockwise
      OnRevReg(OUT_A, 10); //look same but practically on robot due to inertia for motor a speed is speed/2
    }
    else if( currentGyro >180 && currentGyro<325){
      SetLedPattern(LED_GREEN_PULSE);
      OnRevReg(OUT_A, 35); // Moving forward and turning clockwise
      OnRevReg(OUT_D, 8);
    }
    else if(currentGyro <-35 && currentGyro>=-180){
      SetLedPattern(LED_GREEN_PULSE);
      OnRevReg(OUT_A, 35); // Moving forward and turning clockwise
      OnRevReg(OUT_D, 8);
    }
    else if(currentGyro <-180 && currentGyro>=-325){
      SetLedPattern(LED_GREEN_PULSE);
      OnRevReg(OUT_D, 35); // Moving forward and turning anti clockwise
      OnRevReg(OUT_A, 10);
    }
    else{
      SetLedPattern(LED_GREEN_PULSE);
      move_forward(800,100,0,0,1);
      stop();
      break;
    }
  }
}
void ControlExplore(){
  int count = 0;
  if(extOpponetArea == 1){
    ExecuteRetreat();
  }
  if(extInraRedSensor>0 &&extInraRedSensor<=9){
    MoveTowardsBall();
  }
  SetLedPattern(LED_ORANGE);
  while(true){
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
      break;
    }
    if(extOpponetArea == 1){
      ExecuteRetreat();
      break;
    }
    if( 1 == extDetectBall ){
      PushToGoal();
      break;
    }
    if(extInraRedSensor>0 && extInraRedSensor<=9){
      MoveTowardsBall();
      break;
    }
    SetLedPattern(LED_ORANGE);
    if(count < 500){
      OnRevReg(OUT_D, MAXEXPLORE); // Moving forward and turning anti clockwise
      OnRevReg(OUT_A, MINEXPLORE);
      count++;
    }
    else if(count >= 500 && count <900){
      //stop();
      OnRevSync(OUT_AD, MAXEXPLORE);
      count++;
    }
    else{
      move_backward(125,50);
      turn_anticlockwise(40);
      count=0;
    }
    /*
    else if(count < 1000{
    OnFwdReg(OUT_D, MINEXPLORE);
    OnFwdReg(OUT_A, MAXEXPLORE);
    count++;
  }
  else{
  count=0;
}
/*
/*
OnRevReg(OUT_D, MINEXPLORE); // Moving forward and turning clockwise
OnRevReg(OUT_A, MAXEXPLORE);
move_forward(100,30);
move_backward(25,50);
*/
}
}
void ExecuteRetreat(){
  SetLedPattern(LED_RED_PULSE);
  stop();
  extDetectBall = 0;
  extOpponetArea = 0;
  int currentGyro = extGyroSensor - extGyroInitReadingSensor;
  currentGyro = currentGyro %360;
  move_backward(125,70,1);
  if( currentGyro >0 && currentGyro<=180){
    SetLedPattern(LED_RED_PULSE);
    turn_clockwise(90,0,1);
  }
  else if((currentGyro <0 && currentGyro>=-180)){
    SetLedPattern(LED_RED_PULSE);
    turn_anticlockwise(90,0,1);
    //turn_clockwise(90);
  }
  else{
    turn_anticlockwise(90,0,1);
    //turn_clockwise(90);
  }
  move_forward(125,50,1,1);
  //extOpponetArea = 0;
}
