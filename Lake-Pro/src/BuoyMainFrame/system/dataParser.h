#pragma once
#include "../setup/modules.h"

/**
 * @brief Calculates the depth from the reference pressure measured vs. 
 * the pressure outside the cannister under water.
 * @returns Depth in metres.
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
    outsideTemperature  = receivedNumbers[0];
    outsidePressure     = receivedNumbers[1];
    co2_SCD             = receivedNumbers[2];
    temperature_SCD     = receivedNumbers[3];
    humidity_SCD        = receivedNumbers[4];
    pressure_HP20       = receivedNumbers[5];
    humidity_DHT        = receivedNumbers[6];
    temperature_DHT     = receivedNumbers[7];
    oxygenLevel         = receivedNumbers[8];
    CH4_sensorVolt      = receivedNumbers[9];
    CH4ppm              = receivedNumbers[10];
    avg_Temperature     = receivedNumbers[11];
    avg_Humidity        = receivedNumbers[12];

    DEBUG_SERIAL.println(F("+-------------------------+-----------------+"));
    DEBUG_SERIAL.println(F("|        Parameter        |      Value      |"));
    DEBUG_SERIAL.println(F("+-------------------------+-----------------+"));

    // Print each parameter with its corresponding value
    DEBUG_SERIAL.print(F("| Outside Temperature     | "));
    DEBUG_SERIAL.print(receivedNumbers[0], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| Outside Pressure        | "));
    DEBUG_SERIAL.print(receivedNumbers[1], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| CO2 (SCD)               | "));
    DEBUG_SERIAL.print(receivedNumbers[2], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| Temperature (SCD)       | "));
    DEBUG_SERIAL.print(receivedNumbers[3], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| Humidity (SCD)          | "));
    DEBUG_SERIAL.print(receivedNumbers[4], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| Pressure (HP20)         | "));
    DEBUG_SERIAL.print(receivedNumbers[5], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| Humidity (DHT)          | "));
    DEBUG_SERIAL.print(receivedNumbers[6], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| Temperature (DHT)       | "));
    DEBUG_SERIAL.print(receivedNumbers[7], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| Oxygen Level            | "));
    DEBUG_SERIAL.print(receivedNumbers[8], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| CH4 Sensor Voltage      | "));
    DEBUG_SERIAL.print(receivedNumbers[9], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| CH4 ppm                 | "));
    DEBUG_SERIAL.print(receivedNumbers[10], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| Average Temperature     | "));
    DEBUG_SERIAL.print(receivedNumbers[11], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.print(F("| Average Humidity        | "));
    DEBUG_SERIAL.print(receivedNumbers[12], 2);
    DEBUG_SERIAL.println(F("         |"));

    DEBUG_SERIAL.println(F("+-------------------------+-----------------+"));

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