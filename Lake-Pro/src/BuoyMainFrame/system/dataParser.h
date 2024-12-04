#pragma once
#include "../setup/modules.h"

/**
 * @brief Calculates the depth from the reference pressure measured vs. 
 * the pressure outside the cannister under water.
 * 
 */
float calculateDepth(float referencePressure, float outsidePressure){
    depth = (outsidePressure-referencePressure)/(WATER_DENSITY*G_ACC);
    return depth;
}

/**
 * @brief Outputs the depth on the Debug monitor.
 * 
 */
void outputDepth(float depth, float referencePressure){
    DEBUG_SERIAL.println("Depth is " + String(depth));
    DEBUG_SERIAL.println("Ref pressure is " + String(referencePressure));
}

/**
 * @brief Splits the data string received over UART from the cannister to the different global variables.
 * @param data a String with each sensor data separated by a semicolon.
 */
void parseDataFromCannister(String data) {
    int startIndex = 0;
    int endIndex = data.indexOf(";", startIndex);

    floatCount = 0;
    int len_data = (int) data.length();
    
    // Splits the data into a float array, as each data is separated with a semicolon when received.
    while (endIndex != -1 && floatCount < MAX_FLOATS) {
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
    DEBUG_SERIAL.println("CO2   HUMIDITY   TEMPERATURE INSIDE   PRESSURE INSIDE   TEMPERATURE OUTSIDE   PRESSURE OUTSIDE   CH4 SENSORVOLT   CH4 PPM");
    DEBUG_SERIAL.print(co2_SCD);               DEBUG_SERIAL.print("\t \t");
    DEBUG_SERIAL.print(avg_Humidity);          DEBUG_SERIAL.print("\t \t");
    DEBUG_SERIAL.print(avg_Temperature);       DEBUG_SERIAL.print("\t \t");
    DEBUG_SERIAL.print(pressure_HP20);         DEBUG_SERIAL.print("\t \t");
    DEBUG_SERIAL.print(outsideTemperature);    DEBUG_SERIAL.print("\t \t");
    DEBUG_SERIAL.print(outsidePressure);       DEBUG_SERIAL.print("\t \t"); 
    DEBUG_SERIAL.print(CH4_sensorVolt);        DEBUG_SERIAL.print("\t \t");
    DEBUG_SERIAL.println(CH4ppm);


    DEBUG_SERIAL.print("In Equilibrium: ");
    DEBUG_SERIAL.println(inEquilibrium ? "Yes" : "No");
}

/**
 * @brief Sends the data over LoRa by first converting to a command with hexidecimals
 * @param data a String with each sensor data separated by a semicolon.
 */
void sendDataOverLora(String data){
    // Send back the dataString
    String command = "AT+CMSGHEX=\"" + stringToHex(data) + "\"\r\n";
    if (sendCommandAndReceiveResponse("Done")) {
        DEBUG_SERIAL.println("Data string sent successfully.");
    } else {
        DEBUG_SERIAL.println("Failed to send data string.");
    }
}

/**
 * @brief Converts a string to its hexadecimal representation.
 * 
 * @param input The input string to convert.
 * @return String The hexadecimal representation of the input string.
 */
String stringToHex(const String& input) {
    String hex = "";
    for (uint16_t i = 0; i < input.length(); i++) {
        char c = input.charAt(i);
        if (c < 16) hex += '0'; // Pad with 0 for single-digit hex
        hex += String(c, HEX);
    }
    return hex;
}