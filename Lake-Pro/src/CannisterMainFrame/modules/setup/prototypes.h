#pragma once
#include "modules.h"

/* Prototypes */
void SCD30_Measure(float*, float*, float*);
void HP20_Measure(float*);
void DHT22_Measure(float*, float*);
void outsideTemp_Measure(float*);
void preheatMethaneSensor();
void convertCH4SensorToCH4ppm(float*);
void packageAndSendData();
void CH4_Measure(float*);
void calculateAverageTempAndHumidity(float*, float*);
void outsidePressure_Measure(float*);