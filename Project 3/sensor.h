/*
* sensor.h
*
* Created on: Nov 20, 2019
* Author: Team_5
*/
#ifndef SENSOR_H_
#define SENSOR_H_
#include <ev3.h>
extern int extColorSensor;
extern int extGyroSensor;
extern int extInraRedSensor;
extern int extGyroInitReadingSensor;
extern int extTouchSensor;
int setSensor();
int ReadTouchSensor();
int ReadColorSensor();
int ReadGyroSensor();
int ReadInfraRedSensor();
#endif /* SENSOR_H_ */
