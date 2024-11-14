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
    if (Serial1.available()) {
        String data = Serial1.readStringUntil('\n');
        Serial.print("Received data: ");
        Serial.println(data);
        printDataToSDCard(data);
        printTimeToSD();    
    }
}