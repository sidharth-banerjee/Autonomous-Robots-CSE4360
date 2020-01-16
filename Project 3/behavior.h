#ifndef BEHAVIOR_H
#define BEHAVIOR_H
#include "sensor.h"
#include "control.h"
extern int extOpponetArea;
extern int extOpponentColor;
extern int extRedColor;
extern int extGreenColor;
extern int extBlackColor;
extern int extDetectBall;
void FollowBall();
void PushGoal();
void Explore();
void OpponentDefence();
void Retreat();
void DetectBall();
#endif
