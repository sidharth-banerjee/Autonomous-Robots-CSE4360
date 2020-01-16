#ifndef BEHAVIOR_H
#define BEHAVIOR_H
#include "sensor.h"
#include "control.h"
extern int GoalReached;
extern int extNextRoom;
extern int extMaxLeftTurn;
extern int extSightCount;
extern int extMoveBack;
extern int extUnitLength;
extern int extRightAngleTurn;
extern int RIGHTMAXDISTANCE;
void goal_reached();
void follow_wall();
void wander();
void CheckLineofSite();
void ext_fire();
