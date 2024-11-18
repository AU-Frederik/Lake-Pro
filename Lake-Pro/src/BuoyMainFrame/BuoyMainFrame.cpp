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

bool isAMessage = false;
String message = "M10"; // Set manual right now before implementing LoRa

void setup() {
    setupCommunication();
    initAllPins();
    digitalWrite(CannisterON_Pin, HIGH);
    setUpSDCard();

    // Make sure that Rotiny is set to low
    digitalWrite(MOTOR_DOWN_PIN , LOW);
    digitalWrite(MOTOR_UP_PIN   , LOW);
    
}

void loop() {
    measureMotorPins();
    if (manualMode){
        enableManualMode();
    } else {
        reactToCommand();
    }

    // Receives data from cannister via UART, prints to debug monitor and SD card
    receiveFromUARTAndPrintToSDCard();

    // Calculates the depth (change ref_pressure to buoy pressure)
    depth = (outsidePressure-ref_pressure)/(waterDensity*g_acc);
    COM_CANNISTER.println('M');
}

// Measures the three pins of the manual buttons
void measureMotorPins(){
    manualMode   = digitalRead(MOTOR_SWITCH_AUT);
    turnMotorCCW = digitalRead(MOTOR_BUTTON_LEFT);
    turnMotorCW  = digitalRead(MOTOR_BUTTON_RIGHT);
}

// Only call when manualMode is true. Turns motor according to motor buttons pressed
void enableManualMode(){
    if (!turnMotorCCW && turnMotorCW){ 
        moveMotorUp(); // Turn CW
    } else if (turnMotorCCW && !turnMotorCW){
        moveMotorDown();  // Turn CCW
    } else {                                  
        holdMotor();    // Don't move
    }
}

// Reads a command sent from the debug monitor and reacts to it
void reactToCommand(){
    if (!COM_DEBUG.available()){
        return;
    }

    // Read first three letters/number and save to a string
    for (int i = 0; i < 3; i++){
        char incomingChar = COM_DEBUG.read();
        message += incomingChar;
    }

    char firstChar = message.charAt(0);

    // Checks if the first character is either M, B or S (Measure, Battery status, Solar status)
    switch(firstChar) {
        case 'M': 
            goToDepthAndMeasure();
            break;
        case 'B':
            measureBatteryStatus();
            break;
        case 'S':
            measureSolarStatus();
            break;
        default:
            break;
    }
}

void goToDepthAndMeasure() {
    // Extracts the number part of the message and converts to an int
    String numericPart = message.substring(1);
    int destinationDepth = numericPart.toInt();

    // Variables to make code more readable
    int upperLimit = destinationDepth + depthThreshold;
    int lowerLimit = destinationDepth - depthThreshold;
    bool insideTolerance = depth < upperLimit && depth > lowerLimit;

    // if destination depth is not reached move in the right direction
    if (depth > upperLimit && !insideTolerance){
        moveMotorUp();
    } else if (depth < lowerLimit && !insideTolerance){
        moveMotorDown();
    } else {
        holdMotor();
    }

    if (insideTolerance){
        COM_CANNISTER.println('M');
    } else {
        COM_CANNISTER.println('W');
    }
}

void moveMotorUp(){
    digitalWrite(MOTOR_DOWN_PIN, LOW);
    digitalWrite(MOTOR_UP_PIN, HIGH);
}

void moveMotorDown(){
    digitalWrite(MOTOR_DOWN_PIN, HIGH);
    digitalWrite(MOTOR_UP_PIN, LOW);
}

void holdMotor(){
    digitalWrite(MOTOR_DOWN_PIN, LOW);
    digitalWrite(MOTOR_UP_PIN, LOW);
}

// Does nothing right now
void measureBatteryStatus(){;}
void measureSolarStatus(){;}

void receiveFromUARTAndPrintToSDCard(){
    // Receives data from cannister via UART, separates it and prints on SD Card separated by comma.
    if (COM_CANNISTER.available()) {
        // Saves data received via UART from cannister to one long string
        String data = COM_CANNISTER.readStringUntil('\n');
        

        // Split data and add each data element to the global variables
        parseDataFromCannister(data);

        // Add timestamp to line on SD card
        printTimeToSD();

        // Print data to SD card
        printDataToSDCard(data);
    }
}