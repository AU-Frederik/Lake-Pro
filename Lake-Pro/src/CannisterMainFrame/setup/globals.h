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

unsigned long setupTime;

char command;
String sensorDataString;