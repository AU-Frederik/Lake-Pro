// Author: Mechatronics Group 3
// Date: 20th of December, 2024

#pragma once

#include "modules.h"

/* General constants */
#define DHT22_PIN               8
#define DHTTYPE                 DHT22
#define TIME_TO_PREHEAT         60000       // 1 minute - should be longer for actual application
#define FRESH_WATER_DENSITY     997         // kg/m^3
#define TIME_PR_ROUND           3000        // 3 seconds each sensor iteration

/* Communication - Serial */
#define DEBUG_SERIAL               Serial
#define DEBUG_SERIAL_BAUDRATE      9600

#define BUOY_SERIAL                Serial3
#define BUOY_SERIAL_BAUDRATE       9600

#define FD02_SERIAL                Serial1
#define FD02_SERIAL_BAUDRATE       19200
