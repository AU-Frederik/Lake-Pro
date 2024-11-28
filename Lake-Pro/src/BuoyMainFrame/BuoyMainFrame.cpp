// File: BuoyMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

/*
LORA CODES:
M00: Stop measuring and return to top
MXX: Go to XX meters and start measuring. XX = 01-99
B: Check battery status
S: Check solar status
*/

#include "./setup/modules.h"

void setup() {
    runAllSetups();
}

void loop() {
    measureRefPressure(&referencePressure);
    
    command = "M10"; // Set manually

    // Check the manual buttons, S -> Manual mode, R -> Automatic mode
    measureMotorPins();
    unbrakeCable();             // Unbrakes the cable if it is braked.
    if (manualMode){
        enableManualMode();
    } else {
        reactToCommand();
    }

    // Receives data from cannister via UART, prints to debug monitor and SD card
    receiveFromUARTAndPrintToSDCard();

    // Calculates the depth (change ref_pressure to buoy pressure)
    calculateDepth();
    outputDepth();
}



