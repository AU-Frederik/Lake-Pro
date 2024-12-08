// Author: Mechatronics Group 3
// Date: 20th of December, 2024

#pragma once
#include "modules.h"

/* Global variables */
float avg_Temperature;
float avg_Humidity;
unsigned long myTime;

/* Status - Sets to false from start */
bool isBAR100Ready;
bool isSCD30Ready;
bool isADSReady;
bool isHP20xReady;

/* Time */
unsigned long setupTime;

/* Global messages to and from buoy */
char command;
String sensorDataString;