/*
* sensor.cpp
*
* Created on: Nov 20, 2019
* Author: Team_5
*/
#include<string>
#include"sensor.h"
#include<math.h>
int extColorSensor = 0;
int extGyroSensor = 0;
int extInraRedSensor = 0;
int extGyroInitReadingSensor = 0;
int extTouchSensor = 0;
int setSensor(){
  //Input port need to update
  //IN_1 = front sonar
  //IN_2 = light sensor
  //IN_3 = color sensor
  //IN_4 = Right sonar
  //Wait(2000);
  setAllSensorMode(NXT_IR_SEEKER,COL_COLOR,NXT_IR_SEEKER,GYRO_ANG);
  setAllSensorMode(NXT_IR_SEEKER,COL_COLOR,NXT_IR_SEEKER,GYRO_RATE);
  setAllSensorMode(NXT_IR_SEEKER,COL_COLOR,NXT_IR_SEEKER,GYRO_ANG);
  setAllSensorMode(NXT_IR_SEEKER,COL_COLOR,NXT_IR_SEEKER,GYRO_RATE);
  setAllSensorMode(NXT_IR_SEEKER,COL_COLOR,NXT_IR_SEEKER,GYRO_ANG);
  setAllSensorMode(NXT_IR_SEEKER,COL_COLOR,NXT_IR_SEEKER,GYRO_RATE);
  return setAllSensorMode(NXT_IR_SEEKER,COL_COLOR,NXT_IR_SEEKER,GYRO_ANG);
}
int ReadColorSensor(){
  char buffer[5];
  std::string greeting("Color sensor init!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  Wait(2);
  while(true){
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
      break;
    }
    //IN_3 will update according to final design
    extColorSensor = readSensor(IN_2);
  }
  return extColorSensor;
}
int ReadGyroSensor(){
  char buffer[5];
  int localgyro = 0;
  int localgyroold = 0;
  extGyroInitReadingSensor = readSensor(IN_4);
  std::string greeting("Gyro sensor init!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  Wait(2);
  //extGyroSensor = readSensor(IN_1);
  //localgyro = extGyroSensor;
  //localgyroold = extGyroSensor;
  while(true){
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
      break;
    }
    //IN_1 will update according to final design
    extGyroSensor = readSensor(IN_4);
    /*
    if(localgyro !=localgyroold)
    {
    sprintf(buffer, "t sen = %d\n", extGyroSensor);
    LcdPrintf(1,buffer);
    Wait(2);
    localgyroold = localgyro;
  }*/
  //Wait(2000);
  //LcdClean();
}
return extGyroSensor;
}
int ReadInfraRedSensor(){
  char buffer[5];
  std::string greeting("Infra Red sensor init!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  Wait(2);
  while(true){
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
      break;
    }
    //IN_2 will update according to final design
    extInraRedSensor = readSensor(IN_1);
  }
  return extInraRedSensor;
}
int ReadTouchSensor(){
  std::string greeting("Infra Touch sensor init!");
  LcdPrintf(1, "%s\n", greeting.c_str());
  Wait(2);
  while(true){
    if(!ButtonIsUp(BTNUP)){
      FreeEV3();
      break;
    }
    //IN_2 will update according to final design
    extTouchSensor = readSensor(IN_3);
    /*
    if( extTouchSensor >= 4 && extTouchSensor <=6){
    extTouchSensor = 1;
  }
  else{
  extTouchSensor = 0;
}*/
/*
if(extTouchSensor){
std::string greeting("Pressed!");
LcdPrintf(1, "%s\n", greeting.c_str());
}
*/
}
}
