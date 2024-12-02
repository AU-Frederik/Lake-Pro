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

/*
void setup() {
    //runAllSetups();
    initAllPins();
    turnOnCannister();
    //turnOffCableMotor();
    setupCommunication();
    //setupBrakeMotor();
    //setupPressureSensor();
    //setUpSDCard(); 
}

void loop() {
    //measureRefPressure(&referencePressure);
    
    command = "M10"; // Set manually

    if (COM_CANNISTER.available() > 0){
        COM_CANNISTER.println(command);
    } else {
        COM_DEBUG.println("Couldn't print to cannister");
    }
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
    
}
*/


void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  Serial.println("Mega B: Sending handshake...");

  // Send handshake signal to Mega A
  Serial2.println("READY");
  Serial.println("Mega B: Handshake sent. Ready to receive data.");
}

void loop() {
  // Check if data is available from Mega A
  if (Serial2.available() > 0) {
    String receivedMessage = Serial2.readString();
    Serial.print("Received from Mega A: ");
    Serial.println(receivedMessage);
  } else {
    Serial.println("No connection...");
  }
}
