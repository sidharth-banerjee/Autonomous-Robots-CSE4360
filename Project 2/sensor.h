/*
* sensor.h
*
* Created on: Nov 20, 2019
* Author: Team_5
*/
#ifndef SENSOR_H_
#define SENSOR_H_
#include <ev3.h>
extern int TRANSPARENT;
extern int BLACK;
extern int BLUE;
extern int GREEN;
extern int YELLOW;
extern int RED;
extern int WHITE;
extern int BROWN;
extern int FRONTSAFEDISTANCE;
extern int RIGHTSAFEDISTANCE;
extern int extmoveForward;
extern int extmoveRight;
extern int LIGHTTHRESHOLD;
extern int extLineOfsight;
extern int extlightSensor;
extern int extcolorSensor;
extern int extfrontSonarSensor;
extern int extrightSonarSensor;
extern int extSightFlag;
extern int GoalLightThreashold;
extern int LightGoalFlag;
extern int extLightGoalCount;
int setSensor();
void ReadColorSensor();
void ReadLightSensor();
void ReadFrontSonar();
void ReadRightSonar();
#endif /* SENSOR_H_ */
