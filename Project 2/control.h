/*
* control.h
*
* Created on: Nov 20, 2019
* Author: Team_5
*/
#ifndef CONTROL_H
#define CONTROL_H
#include <ev3.h>
extern int sightflag;
//void move_forward(int length,int speed, int* deg_L, int* deg_R,int *clock_offset);
void move_forward(int length,int speed);
void move_backward(int length,int speed);
void turn_clockwise(int theta);
void turn_anticlockwise(int theta);
void RotateFan();
void stop();
void MoveAwayFromRightWall(double remaining_motor_rot,int speed);
#endif
