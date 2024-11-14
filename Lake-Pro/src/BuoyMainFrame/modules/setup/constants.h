#pragma once
#include "modules.h"

#define maxFloats 4  // Number of sensor data that we will receive
#define SENSOR_DATA_FILENAME "results.txt"

/* Communication - Serial */
#define COM_DEBUG                   Serial
#define COM_DEBUG_BAUDRATE          9600

#define COM_CANNISTER               Serial1
#define COM_CANNISTER_BAUDRATE      9600