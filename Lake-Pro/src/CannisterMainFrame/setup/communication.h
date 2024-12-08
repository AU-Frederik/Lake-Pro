// Author: Mechatronics Group 3
// Date: 20th of December, 2024

#pragma once 
#include "modules.h"

/**
 * @brief Setups up I2C, debug serial, buoy serial and FD02 oxygen sensor serial.
 * 
 */
void setupCommunication(){
    // Setup I2C & UART to either PC or BuoyMainFrame Arduino
    Wire.begin();
    DEBUG_SERIAL.begin(DEBUG_SERIAL_BAUDRATE);
    BUOY_SERIAL.begin(BUOY_SERIAL_BAUDRATE);
    FD02_SERIAL.begin(FD02_SERIAL_BAUDRATE, SERIAL_8N1);
}