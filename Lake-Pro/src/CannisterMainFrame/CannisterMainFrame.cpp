// Author: Mechatronics Group 3
// Date: 20th of December, 2024

/*
SYSTEM CONSISTS OF: 
- DHT22                 HUMIDITY AND TEMP SENSOR)
- GROVE SCD30           CO2, HUMIDITY AND TEMP SENSOR
- GROVE BAROMETER       PRESSURE SENSOR INSIDE)
- TSYS01                TEMPERATURE SENSOR IN WATER
- FIGARO NGM2611-E13    CH4 SENSOR THROUGH ADS1115
- BAR100                OUTSIDE PRESSURE AND TEMPERATURE SENSOR
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
    unsigned long loopTime = millis();                  // Measures time before loop starts
    char command = '\0';                                // Resets command to the null character
    String sensorDataString = "";                       // Resets the dataString

    checkInitializationOfSensors();                     // Checks all sensors initiliazation. Initializes if they are not already initialized.

    command = receiveCommandFromBuoy();                 // Receives command from buoy and saves in a char variable

    sensorDataString = measureAll(command);             // Measures on all sensors depending on the command

    sendSensorDataToBuoy(sensorDataString);             // Send data String to the buoy using UART

    unsigned long timeElapsed = millis() - loopTime;    // Time spent in the loop
    if (timeElapsed < TIME_PR_ROUND) {                  // Delays so that the loop takes 3 seconds in total
        delay(TIME_PR_ROUND - timeElapsed);
    }
}



