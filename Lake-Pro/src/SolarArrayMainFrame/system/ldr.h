// Author: Mechatronics Group 3
// Date: 20th of December, 2024

#pragma once
#include "../setup/modules.h"

/**
 * @brief Reads the 4 pins from the LDR sensors and saves them.
 * 
 */
void readLDRSensors() {
    LDR_NORTH_VALUE = analogRead(LDR_NORTH_PIN);
    LDR_SOUTH_VALUE = analogRead(LDR_SOUTH_PIN);
    LDR_EAST_VALUE = analogRead(LDR_EAST_PIN);
    LDR_WEST_VALUE = analogRead(LDR_WEST_PIN);
}

/**
 * @brief Prints the LDR values to the Serial monitor.
 * 
 */
void outputLDRValues() {
    DEBUG_SERIAL.print("LDR_NORTH: ");
    DEBUG_SERIAL.print(LDR_NORTH_VALUE);
    DEBUG_SERIAL.print('\t');
    DEBUG_SERIAL.print("LDR_SOUTH: ");
    DEBUG_SERIAL.print(LDR_SOUTH_VALUE);
    DEBUG_SERIAL.print('\t');
    DEBUG_SERIAL.print("LDR_EAST: ");
    DEBUG_SERIAL.print(LDR_EAST_VALUE);
    DEBUG_SERIAL.print('\t');
    DEBUG_SERIAL.print("LDR_WEST: ");
    DEBUG_SERIAL.println(LDR_WEST_VALUE);
}