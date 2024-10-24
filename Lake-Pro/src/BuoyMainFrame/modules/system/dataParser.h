#pragma once
#include "../setup/modules.h"

// Receives data from cannister via UART, separates it and prints on SD Card separated by comma. 
void receiveDataFromUARTAndPrintToSDCard() {
    if (mySerial.available()) {
        String data = mySerial.readStringUntil('\n');
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

        for (int i=0; i<maxFloats; i++){
            printDataToSDCard(receivedNumbers[i]);
        }
        printTimeToSD();
    }
}