#pragma once

#include "modules.h"

/* Instances */
KalmanFilter      p_filter;
DHT               dht(DHT22_PIN, DHTTYPE);
Adafruit_ADS1115  ads;
TSYS01            outsideTempSensor;
KellerLD          outsidePressureSensor;