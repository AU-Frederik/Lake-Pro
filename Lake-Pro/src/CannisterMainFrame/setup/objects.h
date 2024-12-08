// Author: Mechatronics Group 3
// Date: 20th of December, 2024

#pragma once

#include "modules.h"

/* Instances / Objects */
KalmanFilter      p_filter;
DHT               dht22(DHT22_PIN, DHTTYPE);
Adafruit_ADS1115  ads;
KellerLD          BAR100;