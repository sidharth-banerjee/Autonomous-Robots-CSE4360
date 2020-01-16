#include"control.h"
#include"mymap.h"
#include"mypath.h"
#include<math.h>
int main()
{
  InitEV3();
  ResetRotationCount(OUT_ABCD);
  Point nLocation;
  int *x_pos = (int*)malloc(sizeof(int));
  int *y_pos = (int*)malloc(sizeof(int));
  int *deg_L = (int*)malloc(sizeof(int));
  int *deg_R = (int*)malloc(sizeof(int));
  int *clock_offset = (int*)malloc(sizeof(int));
  int *prev_err = (int*)malloc(sizeof(int));
  int CurrentLocation[2] = {0,0};
  int NextLocation[2] = {0,0};
  *x_pos = 0;
  *y_pos = 0;
  *deg_L = 0;
  *deg_R = 0;
  *clock_offset = 0;
  *prev_err = 0;
  //move_forward(305*10,20, deg_L, deg_R,clock_offset);
  //move_forward(305*1,20, deg_L, deg_R,clock_offset);
  //move_backward(305,50, deg_L, deg_R,clock_offset);
  //turnclockwise(270, 15, deg_L, deg_R,clock_offset);
  /*
  int rotation_speed = 2;
  int move_speed = 4;
  int theta = 90;
  */
  //make_rectangle(deg_L, deg_R);
  //turnanticlockwise(theta, rotation_speed, deg_L, deg_R);
  initializeMap();
  InitializeQueue();
  UpdateMap();
  CreatePath();
  ContractedPath();
  CURRENT_ORIENTATION = 0;
  //starting pos
  contracted.pop();
  CurrentLocation[0] = start_pos[0];
  CurrentLocation[1] = start_pos[1];
  while(!contracted.empty())
  {
    Point nextLoc = contracted.top();
    NextLocation[0] = nextLoc.Col;
    NextLocation[1] = nextLoc.Row;
    contracted.pop();
    ///////////////////////////////////////////////
    MoveToNext(CurrentLocation, NextLocation, deg_L, deg_R, clock_offset);
    /////////////////////////////////////////////////////////////
    CurrentLocation[0] = NextLocation[0];
    CurrentLocation[1] = NextLocation[1];
  }
  //PathTravel(deg_L, deg_R, clock_offset);
  //path(deg_L, deg_R,clock_offset);
  /*
  //...
  int move_speed = 30;
  int err = get_err(305*16,move_speed, deg_L, deg_R,clock_offset);
  char* buffer = (char*)malloc(10*sizeof(char));
  sprintf(buffer, "%d", err);
  LcdPrintf(1,buffer);
  Wait(10000);
  //...
  int err = 0;
  int speed = 20;
  ResetRotationCount(OUT_ABCD);
  //long R = 122.9/2; // in mm
  long c = 175.9; // circumference of wheel in mm
  double motor_rot = (305*8 * 360)/c;
  //RotateMotor(OUT_BC,speed,motor_rot);
  while(MotorRotationCount(OUT_B)<motor_rot)
  {
  if(!ButtonIsUp(BTNUP)){
  FreeEV3();
}
err = err_correction(prev_err);
OnFwdReg(OUT_B, speed + err);
OnFwdReg(OUT_C, speed);
}
//...
//turnclockwise(theta, rotation_speed, deg_L, deg_R);
//move_forward(305*16,move_speed, deg_L, deg_R);
//Stop_Motor();
//turnclockwise(theta, rotation_speed, deg_L, deg_R);
//Stop_Motor();
//move_forward(305*2,move_speed, deg_L, deg_R);
//Stop_Motor();
//turnclockwise(theta, rotation_speed, deg_L, deg_R);
//Stop_Motor();
//move_forward(305*2,move_speed, deg_L, deg_R);
//Stop_Motor();
//turnclockwise(theta, rotation_speed, deg_L, deg_R);
//Stop_Motor();
//move_forward(305*2,move_speed, deg_L, deg_R);
//turnclockwise(theta, rotation_speed, deg_L, deg_R);
//Stop_Motor();
//Stop_Motor();
//accelerate(speed);
//decelerate(speed);
/*
while(ButtonIsUp(BTNUP)){
OnFwdReg(OUT_BC,speed);
}
*/
/*
LcdClean(); // erases the display
int val = 0;
char rotation[7];
ResetRotationCount(OUT_BC);
int count =0;
while(ButtonIsUp(BTNUP)){
OnFwdReg(OUT_B,15); OnFwdReg(OUT_C,15);
if(MotorRotationCount(OUT_B)< MotorRotationCount(OUT_C))
{
LcdPrintf(1,"B is slower" );
}
else if(MotorRotationCount(OUT_B)> MotorRotationCount(OUT_C))
{
LcdPrintf(2,"C is slower" );
}
else
{
LcdPrintf(1,"equal" );
}
count ++;
// sleep();
}
Wait(10000);
*/
free(x_pos);
free(y_pos);
free(deg_L);
free(deg_R);
free(prev_err);
FreeEV3();
return(0);
}
