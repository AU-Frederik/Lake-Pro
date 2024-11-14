// File: BuoyMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

/*
ARDUINO MEGA:
SCK  -> PIN52
MOSI -> PIN51
MISO -> PIN50
CS   -> PIN53
*/

#include "./modules/setup/modules.h"

void setup() {
    setupCommunication();
    initAllPins();
    setUpSDCard();
}

void loop() {
    // Receives data from cannister via UART, separates it and prints on SD Card separated by comma. 
    if (COM_CANNISTER.available()) {
        String data = COM_CANNISTER.readStringUntil('\n');
        COM_DEBUG.print("Received data: ");
        COM_DEBUG.println(data);
        printTimeToSD();
        printDataToSDCard(data);
    }
}