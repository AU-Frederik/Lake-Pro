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
    COM_DEBUG.print("LDR_NORTH: ");
    COM_DEBUG.print(LDR_NORTH_VALUE);
    COM_DEBUG.print('\t');
    COM_DEBUG.print("LDR_SOUTH: ");
    COM_DEBUG.print(LDR_SOUTH_VALUE);
    COM_DEBUG.print('\t');
    COM_DEBUG.print("LDR_EAST: ");
    COM_DEBUG.print(LDR_EAST_VALUE);
    COM_DEBUG.print('\t');
    COM_DEBUG.print("LDR_WEST: ");
    COM_DEBUG.println(LDR_WEST_VALUE);
}