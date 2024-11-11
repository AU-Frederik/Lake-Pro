// File: CannisterMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

/*
SYSTEM RIGHT NOW CONSISTS OF: 
- DHT22 (HUMIDITY AND TEMP SENSOR)
- GROVE SCD30 (CO2, HUMIDITY AND TEMP SENSOR)
- GROVE BAROMETER (PRESSURE SENSOR INSIDE)
- TSYS01 (TEMP SENSOR IN WATER)
- FIGARO NGM2611-E13 (CH4 SENSOR) THROUGH ADS1115 (ADC)

MISSING: 
- BAR100 (OUTSIDE PRESSURE SENSOR)
*/

#include "./modules/setup/modules.h"

void setup() 
{
    setupCommunication();
    initSensors();
    // preheatMethaneSensor(); // uncomment to preheat
    delay(1000);
}

void loop() 
{
    // String to hold the data package - resets every loop
    dataString = "";

    // Measure CO2, Temperature (in & out), pressure, humidity and CH4 (sensor volt & ppm)
    measureAll();
    packageAndSendData();
    delay(3000); //Dont change - SCD30 only works at 2.1 seconds delay or above.
}