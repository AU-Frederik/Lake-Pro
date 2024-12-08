// Author: Mechatronics Group 3
// Date: 20-12-2024

#pragma once
#include "modules.h"

// Sets up the different communication ways
void setupCommunication(){
    Wire.begin();                                   // I2C 
    DEBUG_SERIAL.begin(DEBUG_SERIAL_BAUDRATE);            // For printing to monitor
    CANNISTER_SERIAL.begin(CANNISTER_SERIAL_BAUDRATE);    // For RX/TX to cannister
}