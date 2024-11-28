#pragma once

#include "modules.h"

#define DHT22_PIN 8
#define DHTTYPE DHT22
#define timeToPreheat 0 // 0 seconds

/* Communication - Serial */
#define COM_DEBUG           Serial
#define COM_DEBUG_BAUDRATE  9600

#define COM_BUOY            Serial2
#define COM_BUOY_BAUDRATE   9600

#define COM_FD02            Serial1
#define COM_FD02_BAUDRATE   19200
