#pragma once
#include "../setup/modules.h"

// Receives data from cannister via UART, separates it and prints on SD Card separated by comma. 
void parseDataFromCannister(String data) {
    if (COM_CANNISTER.available()) {
        int startIndex = 0;
        int endIndex = data.indexOf(";", startIndex);
        floatCount = 0;
        int len_data = (int) data.length();
        
        while (endIndex != -1 && floatCount < maxFloats) {
            String token = data.substring(startIndex, endIndex); // saves next number as token, seperatered by ";"
            receivedNumbers[floatCount] = token.toFloat();
            startIndex = endIndex + 1;
            floatCount++;
            endIndex = data.indexOf(";", startIndex);
            if (startIndex > len_data) break; // To prevent "out of array bounds"
        }
    }

    // After having split the numbers, each is saved to the global variables
    co2_SCD             = receivedNumbers[1];
    avg_Humidity        = receivedNumbers[2];
    avg_Temperature     = receivedNumbers[3];
    pressure_HP20       = receivedNumbers[4];
    outsideTemperature  = receivedNumbers[5];
    CH4_sensorVolt      = receivedNumbers[6];
    outsidePressure     = receivedNumbers[7];
    depth               = receivedNumbers[8];
    CH4ppm              = receivedNumbers[9];
}