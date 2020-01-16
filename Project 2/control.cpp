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
int sightflag = 1;
void MoveAwayFromRightWall(double remaining_motor_rot,int speed)
{
  ResetRotationCount(OUT_ABCD);
  turn_anticlockwise(5);
  //motor_rot = motor_rot*5.0;
  while(MotorRotationCount(OUT_D)<remaining_motor_rot)
  {
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
    }
    OnFwdSync(OUT_AD, speed);
    if(GoalReached ==1 || extmoveForward == 0 ){
      stop();
      break;
    }
  }
  stop();
  extmoveRight = 1;
}
void move_forward(int length,int speed){
  ResetRotationCount(OUT_ABCD);
  char buffer[15];
  char vbuffer[15];
  long c = 175.9; // circumference of wheel in mm
  double motor_rot = (length * 360)/c;
  double remaining_motor_cnt = motor_rot;
  if(extmoveRight ==0){
    MoveAwayFromRightWall(remaining_motor_cnt,speed);
  }
  //motor_rot = motor_rot*5.0;
  while(MotorRotationCount(OUT_D)<motor_rot)
  {
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
    }
    if(GoalReached ==1 || extmoveForward == 0 || extmoveRight==0){
      remaining_motor_cnt = remaining_motor_cnt - MotorRotationCount(OUT_D);
      /*
      sprintf(buffer, "mf = %d\n,", extfrontSonarSensor);
      LcdPrintf(1,buffer);
      Wait(2000);
      sprintf(vbuffer, "mr = %d\n,", extrightSonarSensor);
      LcdPrintf(1,vbuffer);
      Wait(2000);
      */
      stop();
      if(extmoveRight ==0){
        MoveAwayFromRightWall(remaining_motor_cnt,speed);
      }
      break;
    }
    else{
      OnFwdSync(OUT_AD, speed);
    }
  }
  stop();
}
void move_backward(int length,int speed){
  ResetRotationCount(OUT_ABCD);
  long c = 175.9; // circumference of wheel in mm
  double motor_rot = (length * 360)/c;
  double remaining_motor_cnt = motor_rot;
  if(extmoveRight ==0){
    MoveAwayFromRightWall(remaining_motor_cnt,speed);
  }
  //motor_rot = motor_rot*5.0;
  while(-1*MotorRotationCount(OUT_D)<motor_rot)
  {
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
    }
    //OnRevSync(OUT_AD, speed);
    if(GoalReached ==1 || extmoveForward == 0 || extmoveRight ==0){
      remaining_motor_cnt = remaining_motor_cnt - MotorRotationCount(OUT_D);
      stop();
      break;
    }
    else{
      OnRevSync(OUT_AD, speed);
    }
  }
  stop();
}
void turn_clockwise(int theta){
  //move_backward(5,10);
  ResetRotationCount(OUT_ABCD);
  //speed = 8; // change this to turn at different speed
  long R = 90/2; // in mm
  long c = 175.9; // circumference of wheel in mm
  double motor_rot =( R * theta * M_PI * 360)/ (180 * c);
  while(MotorRotationCount(OUT_A) < motor_rot){
    if(extLineOfsight == 1){
      if(sightflag == 1){
        stop();
        sightflag = 0;
        break;
      }
    }
    OnFwdReg(OUT_A, 12);
    OnRevReg(OUT_D, 12);
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
    }
  }
  extmoveRight = 1;
  extmoveForward = 1;
  //SetLedPattern(LED_BLACK);
  stop();
}
void turn_anticlockwise(int theta){
  //move_backward(5,10);
  ResetRotationCount(OUT_ABCD);
  //speed = 8; // change this to turn at different speed
  long R = 90/2; // in mm
  long c = 175.9; // circumference of wheel in mm
  double motor_rot =( R * theta * M_PI * 360)/ (180 * c);
  while(MotorRotationCount(OUT_D) < motor_rot){
    if(extLineOfsight == 1){
      if(sightflag == 1){
        stop();
        sightflag = 0;
        break;
      }
    }
    OnFwdReg(OUT_D, 12);
    OnRevReg(OUT_A, 12);
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
    }
  }
  extmoveRight = 1;
  extmoveForward = 1;
  //SetLedPattern(LED_BLACK);
  stop();
}
void RotateFan()
{
  ResetRotationCount(OUT_ABCD);
  int rotate_count = 500;
  while(MotorRotationCount(OUT_B) < rotate_count ){
    OnFwdReg(OUT_B, 90);
    if(!ButtonIsUp(BTNUP))
    {
      FreeEV3();
    }
  }
}
void turn_anticlockwisenew(int theta){
  ResetRotationCount(OUT_ABCD);
  RotateMotor(OUT_D, 10,theta);
  extmoveRight = 1;
  extmoveForward = 1;
  //SetLedPattern(LED_BLACK);
  stop();
}
void turn_clockwisenew(int theta){
  ResetRotationCount(OUT_ABCD);
  RotateMotor(OUT_A, 10,theta);
  extmoveRight = 1;
  extmoveForward = 1;
  //SetLedPattern(LED_BLACK);
  stop();
}
void stop()
{
  Off(OUT_ABCD);
}
