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
    /*
    measureMotorPins();
    unbrakeCable();             // Unbrakes the cable if it is braked.
    if (manualMode){
        enableManualMode();
    } else {
        reactToCommand(commandReceivedFromLora);
    }
    */

    bool sendCheck = sendCommandToCannisterAndReceiveData(commandReceivedFromLora.charAt(0));
    DEBUG_SERIAL.println(sendCheck ? "Command sent and acknowledgement returned back." : "No connection to cannister.");

    String dataString = receiveDataFromCannisterAndRespond();

    parseDataFromCannister(dataString);
    printTimeToSD();
    printDataToSDCard(dataString);

    // Calculates the depth and outputs with reference pressure
    depth = calculateDepth(referencePressure, outsidePressure);
    outputDepth(depth, referencePressure);
}

bool sendCommandToCannisterAndReceiveData(char command, unsigned long timeout){
    CANNISTER_SERIAL.println(command);      // Send message to buoy
    DEBUG_SERIAL.print("Sending command: ");
    DEBUG_SERIAL.println(command);

    String response = "";
    unsigned long startTime = millis();
    // Checks for response before set time out
    while (millis() - startTime < timeout) {
        if (CANNISTER_SERIAL.available() > 0) {
            CANNISTER_SERIAL.readStringUntil('\n');

            if (response.indexOf("ACK") >= 0) {
                return true;  // Acknowledgement received
            }
        }
    }
    return false;  // Timeout or response not received
}

String receiveDataFromCannisterAndRespond(){
    String received = "";
    unsigned long startTime = millis();

    // Checks for response before set timeout
    while (millis() - startTime < 5000){
        if (CANNISTER_SERIAL.available() > 0) {
            received = CANNISTER_SERIAL.readStringUntil('\n');
            DEBUG_SERIAL.print("Received: ");
            DEBUG_SERIAL.println(received);
            CANNISTER_SERIAL.println("ACK");
        }
    }
    return received;  // Return received data
}
