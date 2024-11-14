#pragma once
#include "modules.h"

// Sets up the different communication ways
void setupCommunication(){
    Wire.begin();               // I2C 
    COM_DEBUG.begin(COM_DEBUG_BAUDRATE);          // For printing to monitor
    COM_CANNISTER.begin(COM_CANNISTER_BAUDRATE);  // For RX/TX to cannister
}