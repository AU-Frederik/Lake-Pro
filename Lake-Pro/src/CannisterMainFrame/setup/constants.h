#pragma once

#include "modules.h"

#define DHT22_PIN               8
#define DHTTYPE                 DHT22
#define TIME_TO_PREHEAT         1000       // 10 seconds
#define FRESH_WATER_DENSITY     997         // kg/m^3
#define TIME_PR_ROUND           3000        // 10 seconds each sensor iteration

/* Communication - Serial */
#define DEBUG_SERIAL               Serial
#define DEBUG_SERIAL_BAUDRATE      9600

#define BUOY_SERIAL                Serial3
#define BUOY_SERIAL_BAUDRATE       9600

#define FD02_SERIAL                Serial1
#define FD02_SERIAL_BAUDRATE       19200
