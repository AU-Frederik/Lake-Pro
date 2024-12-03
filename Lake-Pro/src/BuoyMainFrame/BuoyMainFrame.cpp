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
    initAllPins();
    turnOnCannister();
    turnOffCableMotor();
    setupCommunication();
    setupBrakeMotor();
    setupPressureSensor();
    setUpSDCard();
}

void loop() {
    float referencePressure = measureRefPressure();
    
    String commandReceivedFromLora = "M10"; // Set manually right now

    // Check the manual buttons, S -> Manual mode, R -> Automatic mode
    measureMotorPins();
    unbrakeCable();             // Unbrakes the cable if it is braked.
    if (manualMode){
        enableManualMode();
    } else {
        reactToCommand(commandReceivedFromLora);
    }

    bool sendCheck = sendCommandToCannisterAndReceiveResponse(commandReceivedFromLora.c_str(), 5000);
    DEBUG_SERIAL.println(sendCheck ? "Command sent and acknowledgement returned back." : "No connection to cannister.");

    char* dataString = receiveDataFromCannisterAndRespond(5000);

    parseDataFromCannister(dataString);
    printTimeToSD();
    printDataToSDCard(dataString);

    // Calculates the depth and outputs with reference pressure
    depth = calculateDepth(referencePressure, outsidePressure);
    outputDepth(depth, referencePressure);
}

bool sendCommandToCannisterAndReceiveResponse(const char* message, unsigned long timeout){
    CANNISTER_SERIAL.println(message);      // Send message to buoy
    
    unsigned long startTime = millis();
    // Checks for response before set time out
    while (millis() - startTime < timeout) {
        if (CANNISTER_SERIAL.available() > 0) {
            char response[10];
            CANNISTER_SERIAL.readBytesUntil('\n', response, sizeof(response));
            response[9] = '\0'; // Ensure null-termination

            if (strcmp(response, "ACK") == 0) {
                return true;  // Acknowledgement received
            }
        }
    }
    return false;  // Timeout or response not received
}

char* receiveDataFromCannisterAndRespond(unsigned long timeout){
    unsigned long startTime = millis();
    static char received[256];

    // Checks for response before set timeout
    while (millis() - startTime < timeout) {
        if (CANNISTER_SERIAL.available() > 0) {
            CANNISTER_SERIAL.readBytesUntil('\n', received, sizeof(received));
            received[sizeof(received) - 1] = '\0'; // Ensure null-termination
            CANNISTER_SERIAL.println("ACK");
            break;  // Exit loop after receiving data
        }
    }
    return received;  // Return received data
}
