// File: BuoyMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

#include "./modules/setup/modules.h"

void setup() {
    setupCommunication();
    initAllPins();
    setUpSDCard();
    // Uncomment for setting time and date 
    showRTCTimeSettings();
}

void loop() {
    // Uncomment for setting time and date from serial monitor input
    setRTCTimeFromSerialInput();
    receiveDataFromUARTAndPrintToSDCard();
    printTime();
}
