#pragma once
#include "../setup/modules.h"

/**
 * @brief Calculates the depth from the reference pressure measured vs. 
 * the pressure outside the cannister under water.
 * 
 */
void calculateDepth(){
    depth = (outsidePressure-referencePressure)/(waterDensity*g_acc);
}

/**
 * @brief Outputs the depth on the Debug monitor.
 * 
 */
void outputDepth(){
    COM_DEBUG.println("Depth is" + String(depth));
    COM_DEBUG.println("Ref pressure is " + String(referencePressure));
}

/**
 * @brief Reads a String from the cannister, splits the data to into variables and prints the time + data to the SD card.
 * 
 */
void receiveFromUARTAndPrintToSDCard(){
    // Receives data from cannister via UART, separates it and prints on SD Card separated by comma.
    if (COM_CANNISTER.available()) {
        // Saves data received via UART from cannister to one long string
        dataString = COM_CANNISTER.readStringUntil('\n');
        // Split data and add each data element to the global variables
        COM_DEBUG.println("Parses data from cannister...");
        parseDataFromCannister(dataString);

        // Add timestamp to line on SD card
        COM_DEBUG.println("Prints time to SD...");
        printTimeToSD();

        // Print data to SD card
        COM_DEBUG.println("Prints data and time to SD card...");
        printDataToSDCard(dataString);
    } else {
        COM_DEBUG.println("Cum cannister not available.");
    }
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
    COM_DEBUG.print(co2_SCD);               COM_DEBUG.print("\t \t");
    COM_DEBUG.print(avg_Humidity);          COM_DEBUG.print("\t \t");
    COM_DEBUG.print(avg_Temperature);       COM_DEBUG.print("\t \t");
    COM_DEBUG.print(pressure_HP20);         COM_DEBUG.print("\t \t");
    COM_DEBUG.print(outsideTemperature);    COM_DEBUG.print("\t \t");
    COM_DEBUG.print(outsidePressure);       COM_DEBUG.print("\t \t"); 
    COM_DEBUG.print(CH4_sensorVolt);        COM_DEBUG.print("\t \t");
    COM_DEBUG.println(CH4ppm);
}

/**
 * @brief Sends the data over LoRa by first converting to a command with hexidecimals
 * @param data a String with each sensor data separated by a semicolon.
 */
void sendDataOverLora(String data){
    // Send back the dataString
    String command = "AT+CMSGHEX=\"" + stringToHex(data) + "\"\r\n";
    if (sendCommandAndReceiveResponse("Done")) {
        COM_DEBUG.println("Data string sent successfully.");
    } else {
        COM_DEBUG.println("Failed to send data string.");
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