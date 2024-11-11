#pragma once

#include "modules.h"

/* Instance */
KalmanFilter p_filter;    //pressure filter
DHT dht(DHT22_PIN, DHTTYPE);
Adafruit_ADS1115 ads;
TSYS01 outsideTempSensor;