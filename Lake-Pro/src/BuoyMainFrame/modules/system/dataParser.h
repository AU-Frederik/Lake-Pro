#pragma once
#include "../setup/modules.h"

// Receives data from cannister via UART, separates it and prints on SD Card separated by comma. 
void parseDataFromCannister(String data) {
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
    

    // After having split the numbers, each is saved to the global variables
    co2_SCD             = receivedNumbers[0];
    avg_Humidity        = receivedNumbers[1];
    avg_Temperature     = receivedNumbers[2];
    pressure_HP20       = receivedNumbers[3];
    outsideTemperature  = receivedNumbers[4];
    outsidePressure     = receivedNumbers[5];
    CH4_sensorVolt      = receivedNumbers[6];
    CH4ppm              = receivedNumbers[7];

    // Print data received to the debugger monitor
    COM_DEBUG.println("CO2   HUMIDITY   TEMPERATURE INSIDE   PRESSURE INSIDE   TEMPERATURE OUTSIDE   PRESSURE OUTSIDE   CH4 SENSORVOLT   CH4 PPM");
    COM_DEBUG.print(co2_SCD);
    COM_DEBUG.print("\t \t");
    COM_DEBUG.print(avg_Humidity);
    COM_DEBUG.print("\t \t");
    COM_DEBUG.print(avg_Temperature);
    COM_DEBUG.print("\t \t");
    COM_DEBUG.print(pressure_HP20);
    COM_DEBUG.print("\t \t");
    COM_DEBUG.print(outsideTemperature);
    COM_DEBUG.print("\t \t");
    COM_DEBUG.print(outsidePressure);
    COM_DEBUG.print("\t \t");
    COM_DEBUG.print(CH4_sensorVolt);
    COM_DEBUG.print("\t \t");
    COM_DEBUG.println(CH4ppm);
}