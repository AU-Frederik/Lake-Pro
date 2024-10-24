// File: BuoyMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

#include "./modules/setup/modules.h"

void setup() {
    Wire.begin();
    pinMode(CSPin, OUTPUT);
    Serial.begin(9600);
    softSerial.begin(9600);
    setUpSDCard();
}

void loop() {
    receiveDataFromUARTAndPrintToSDCard();
}
