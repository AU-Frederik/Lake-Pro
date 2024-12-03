#pragma once
#include "modules.h"

/* Prototypes */
float*  SCD30_Measure();
float   HP20_Measure();
float*  DHT22_Measure();
float*  FIGARO_Measure();
float*  BAR100_Measure();
float   oxygen_Measure();
float   convertCH4SensorToCH4ppm(float CH4ppm);
char*   measureAll(char);
char    receiveCommandFromBuoyAndSendResponse();
bool    sendToBuoyAndReceiveResponse(const char*, unsigned long);

void    checkInitializationOfSensors();
void    initializeDHT22();
bool    isMethaneSensorPreheated();