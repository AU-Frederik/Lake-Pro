#pragma once

#include "SCD30.h"
#include <HP20x_dev.h>
#include "Arduino.h"
#include "Wire.h" 
#include <KalmanFilter.h>
#include <DHT.h>
#include <Adafruit_ADS1X15.h>
#include <TSYS01.h>

// Setup files
#include "constants.h"
#include "objects.h"
#include "prototypes.h"
#include "globals.h"
#include "communication.h"
#include "sensors.h"

// System files
#include "../system/sensorMeasurements.h"
#include "../system/dataParser.h"