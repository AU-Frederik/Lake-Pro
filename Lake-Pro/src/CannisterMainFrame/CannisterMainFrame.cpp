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

    // Receive command
    // Measure on all sensors that are initialized
    checkInitializationOfSensors();

    
    //unsigned long loopTime = millis();
    char command = receiveCommandFromBuoyAndSendResponse();
    String measurements = measureAll(command);
    bool sendCheck = sendToBuoyAndReceiveResponse(measurements, 5000);
    DEBUG_SERIAL.println(sendCheck ? "Sent data and received ACK" : "Sending data failed.");
    //delay(abs(loopTime - TIME_PR_ROUND)); // Delay so that the loop takes exactly 10 seconds
    delay(3000);
}

 bool sendToBuoyAndReceiveResponse(String message, unsigned long timeout){
    DEBUG_SERIAL.println(message);
    BUOY_SERIAL.println(message);      // Send message to buoy
    
    unsigned long startTime = millis();
    // Checks for response before set time out
    while (millis() - startTime < timeout) {
        if (BUOY_SERIAL.available() > 0) {
            char response[10];
            BUOY_SERIAL.readBytesUntil('\n', response, sizeof(response));
            response[sizeof(response) - 1] = '\0'; // Ensure null-termination

            if (strcmp(response, "ACK") == 0) {
                return true;
            }
        }
    }
    return false;  // Timeout or response not received
}

char receiveCommandFromBuoyAndSendResponse(){
    char command = '\0';  // Default to null character

    if (BUOY_SERIAL.available() > 0) {
        command = BUOY_SERIAL.read();  // Read a single character
        BUOY_SERIAL.println("ACK");  // Acknowledge the received command
    }

    return command;
}