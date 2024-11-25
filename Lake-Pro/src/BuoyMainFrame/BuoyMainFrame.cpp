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
    turnOnCannister();
    setupCommunication();
    initAllPins();
    setupBrakeMotor();
    setupPressureSensor();
    setUpSDCard();

    // Make sure that Rotiny is shut off before starting
    holdMotor();
}

void loop() {
    // Check if barometer is ready, if yes measure pressure in hPa
    
    measureRefPressure(&referencePressure);

    message = "M10"; // Set manual right now before implementing LoRa
    String command = "AT+MSGHEX=\"" + stringToHex(message) + "\"";

    measureMotorPins();
    if (manualMode){
        unbrakeCable(); // Unbrakes the cable if it is braked.
        enableManualMode();
    } else {
        unbrakeCable(); // Unbrakes the cable if it is braked.
        reactToCommand();
    }

    // Receives data from cannister via UART, prints to debug monitor and SD card
    receiveFromUARTAndPrintToSDCard();

    // Calculates the depth (change ref_pressure to buoy pressure)
    calculateDepth();
    COM_DEBUG.println("Depth is" + String(depth));
    COM_DEBUG.println("Ref pressure is " + String(referencePressure));
}

