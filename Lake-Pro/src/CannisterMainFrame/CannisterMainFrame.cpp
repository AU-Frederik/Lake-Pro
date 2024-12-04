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
    setupTime = millis();   // Starts the time
    setupCommunication();   // Sets up I2C and Serial communication
    initAllSensors();       // Initiliazes all sensors
}

void loop(){
    unsigned long loopTime = millis();

    checkInitializationOfSensors();

    char command = receiveCommandFromBuoy();
    
    String sensorDataString = measureAll(command);

    sendSensorDataToBuoy(sensorDataString);

    unsigned long timeElapsed = millis() - loopTime;  // Time spent in the loop
    if (timeElapsed < TIME_PR_ROUND) {
        delay(TIME_PR_ROUND - timeElapsed);
    }
}

void sendSensorDataToBuoy(String sensorDataString){
    if (BUOY_SERIAL.available() > 0 && sensorDataString.length() > 5){
        BUOY_SERIAL.println(sensorDataString);
        DEBUG_SERIAL.print("Sending data to buoy: ");
        DEBUG_SERIAL.println(sensorDataString);
    }
}

char receiveCommandFromBuoy(){
    char command = '\0';  // Default to null character

    if (BUOY_SERIAL.available() > 0) {
        command = BUOY_SERIAL.read();  // Read a single character
    }

    return command;
}