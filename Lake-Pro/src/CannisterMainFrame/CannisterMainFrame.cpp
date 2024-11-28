// File: CannisterMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

/*
SYSTEM CONSISTS OF: 
- DHT22                 HUMIDITY AND TEMP SENSOR)
- GROVE SCD30           CO2, HUMIDITY AND TEMP SENSOR
- GROVE BAROMETER       PRESSURE SENSOR INSIDE)
- TSYS01                TEMPERATURE SENSOR IN WATER
- FIGARO NGM2611-E13    CH4 SENSOR THROUGH ADS1115
- BAR100                OUTSIDE PRESSURE SENSOR - NOT TESTED YET
- FD02                  OXYGEN SENSOR
*/

#include "./setup/modules.h"

void setup() 
{
    // Starts the time
    startTime = millis();
    delay(100);
    
    // Sets up I2C and Serial communication
    setupCommunication();

    COM_DEBUG.println("Setting up sensors...");
    // Initiliazes all sensors
    initSensors();
    COM_DEBUG.println("Finished setting up communication...");

    delay(1000);
}

void loop() 
{
    // Read message received from buoy - if 'M' is received it starts measuring on all sensors
    //command = COM_BUOY.readStringUntil('\n');
    command = 'M';
    COM_DEBUG.print("Received message: ");
    COM_DEBUG.println(command);

    // String to hold the data package - resets every loop
    dataString = "";

    // Measure CO2, Temperature (in & out), pressure, humidity and CH4 (sensor volt & ppm)
    measureAll();
    COM_DEBUG.println("Finished oxygen measurements.");
    //packageAndSendData();
    testData();
    delay(3000); // Dont change - SCD30 only works at 2.1 seconds delay or above.
}