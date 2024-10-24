#pragma once
#include "../setup/modules.h"

// Receives data from cannister via UART, separates it and prints on SD Card separated by comma. 
void receiveDataFromUARTAndPrintToSDCard() {
    if (softSerial.available() > 0) {
        parseData();

        // Print all numbers in receivedNumbers to SD Card separated with a comma 
        for (int i=0; i<floatCount; i++){
            printDataToSDCard(receivedNumbers[i]);
        }
    }
}

// Reads data from cannister, parses it and saves the floats to a float array
void parseData() {
    String data = softSerial.readStringUntil('\n');
        int startIndex = 0;
        int endIndex = data.indexOf(";", startIndex);
        int floatCount = 0;
        int len_data = (int) data.length();

        while (floatCount < maxFloats) {
            String token = data.substring(startIndex, endIndex); // saves next number as token, seperatered by ";"
            receivedNumbers[floatCount] = token.toFloat();
            startIndex = endIndex + 1;
            floatCount++;
            endIndex = data.indexOf(";", startIndex);
            if (startIndex > len_data) break; // To prevent "out of array bounds"
        }
}