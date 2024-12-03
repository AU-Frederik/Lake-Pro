#pragma once

#include "modules.h"

/* Instances */
KalmanFilter      p_filter;
DHT               dht22(DHT22_PIN, DHTTYPE);
Adafruit_ADS1115  ads;
KellerLD          BAR100;