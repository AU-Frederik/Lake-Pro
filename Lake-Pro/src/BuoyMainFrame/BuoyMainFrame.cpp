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

#include "./modules/setup/modules.h"

void setup() {
    setupCommunication();
    setupBrakeMotor();
    initAllPins();
    digitalWrite(CannisterON_Pin, HIGH);
    setUpSDCard();

    // Make sure that Rotiny is shut off before starting
    holdMotor();
}

void loop() {
    message = "M10"; // Set manual right now before implementing LoRa
    measureMotorPins();
    if (manualMode){
        enableManualMode();
    } else {
        reactToCommand();
    }

    // Receives data from cannister via UART, prints to debug monitor and SD card
    receiveFromUARTAndPrintToSDCard();

    // Calculates the depth (change ref_pressure to buoy pressure)
    calculateDepth();
    brakeCable();
    unbrakeCable();
}

