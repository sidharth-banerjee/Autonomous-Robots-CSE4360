/*
* control.h
*
* Created on: Nov 20, 2019
* Author: Team_5
*/
#ifndef CONTROL_H
#define CONTROL_H
#include <ev3.h>
#define MAXPUSHFRD 15
#define MINPUSHFRD 5
#define MAXEXPLORE 35
#define MINEXPLORE 25
#define MAXFOLLOW 15
#define MINFOLLOW 5
extern int extMoveLength;
extern int extSwitchtoFollow;
//void move_forward(int length,int speed, int* deg_L, int* deg_R,int *clock_offset);
void move_forward(int length,int speed,int sync = 1,int Retreat = 0,int push = 0);
void move_backward(int length,int speed,int Retreat = 0);
void turn_clockwise(int theta,int GyroFlg=0,int Retreat = 0);
void turn_anticlockwise(int theta,int GyroFlg=0,int Retreat = 0);
void MoveTowardsBall();
void stop();
void PushToGoal();
void ExecuteRetreat();
void ControlExplore();
#endif
