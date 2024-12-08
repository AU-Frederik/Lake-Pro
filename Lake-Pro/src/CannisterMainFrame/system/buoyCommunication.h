// Author: Mechatronics Group 3
// Date: 20th of December, 2024

#pragma once
#include "../setup/modules.h"

void sendSensorDataToBuoy(String sensorDataString){
    if (BUOY_SERIAL.available() > 0 && sensorDataString.length() > 5){
        BUOY_SERIAL.println(sensorDataString);
        printAvailabilityOfSensors();
        DEBUG_SERIAL.print("Sending data to buoy: ");
        DEBUG_SERIAL.println(sensorDataString);

        clearSerialBuffer();
    }
}

char receiveCommandFromBuoy() {
    char command = '\0';  // Default to no command

    while (BUOY_SERIAL.available() > 0) {
        char incoming = BUOY_SERIAL.read();
        // Ignore newline and carriage return
        if (incoming == '\r' || incoming == '\n') {
            continue;
        }

        // If a valid command is found, return it
        if (incoming == 'M' || incoming == 'W') {  // assuming M or W are valid commands
            command = incoming;
            break;  // Exit loop after receiving the first valid command
        }
    }

    DEBUG_SERIAL.print("Command received: ");
    DEBUG_SERIAL.println(command);

    return command;
}

/**
 * @brief Continuously reads and discards all bytes in the serial buffer.
 * 
 */
void clearSerialBuffer() {
    while (BUOY_SERIAL.available() > 0) {
        BUOY_SERIAL.read();  // Discard the byte
    }
}