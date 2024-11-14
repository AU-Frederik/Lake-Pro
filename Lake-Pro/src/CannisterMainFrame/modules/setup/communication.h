#pragma once 
#include "modules.h"

void setupCommunication(){
    // Setup I2C & UART to either PC or BuoyMainFrame Arduino
    Wire.begin();
    Serial.begin(9600);
    Serial1.begin(9600);
}