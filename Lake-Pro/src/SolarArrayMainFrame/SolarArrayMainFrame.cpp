// File: SolarArrayMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

#include "setup/modules.h"

void setup() {
    COM_DEBUG.begin(9600);
    initAllPins();
}

void loop() {
    readLDRSensors();
    formatOutput();
}


// Functions
void readLDRSensors() {
    LDR_NORTH_VALUE = analogRead(LDR_NORTH_PIN);
    LDR_SOUTH_VALUE = analogRead(LDR_SOUTH_PIN);
    LDR_EAST_VALUE = analogRead(LDR_EAST_PIN);
    LDR_WEST_VALUE = analogRead(LDR_WEST_PIN);
}

void formatOutput() {
    COM_DEBUG.print("Difference between North and south values are: ");
    COM_DEBUG.println(LDR_NORTH_VALUE-LDR_SOUTH_VALUE);

    COM_DEBUG.print("Difference between East and West values are: ");
    COM_DEBUG.println(LDR_EAST_VALUE-LDR_WEST_VALUE);

    COM_DEBUG.println("");
}