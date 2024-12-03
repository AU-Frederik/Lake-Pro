#pragma once
#include "modules.h"

/* Prototypes */
float*  SCD30_Measure();
float   HP20_Measure();
float*  DHT22_Measure();
float*  FIGARO_Measure(float);
float*  BAR100_Measure();
float   oxygen_Measure();
float   convertCH4SensorToCH4ppm(float);
String  measureAll(char);
char    receiveCommandFromBuoyAndSendResponse();
bool    sendToBuoyAndReceiveResponse(String, unsigned long);
void    initAllSensors();

void    checkInitializationOfSensors();
bool    isMethaneSensorPreheated();