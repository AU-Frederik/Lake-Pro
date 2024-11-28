#pragma once 
#include "modules.h"

/**
 * @brief Setups up I2C, debug serial, buoy serial and FD02 oxygen sensor serial.
 * 
 */
void setupCommunication(){
    // Setup I2C & UART to either PC or BuoyMainFrame Arduino
    Wire.begin();
    COM_DEBUG.begin(COM_DEBUG_BAUDRATE);
    COM_BUOY.begin(COM_BUOY_BAUDRATE);
    COM_FD02.begin(COM_FD02_BAUDRATE, SERIAL_8N1);
}