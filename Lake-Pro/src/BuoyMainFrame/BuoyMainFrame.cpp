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
String message;

void setup() {
    setupCommunication();
    initAllPins();
    setUpSDCard();
    // showRTCTimeSettings(); // Uncomment to set time

    digitalWrite(MOTOR_CW_PIN, LOW);
    digitalWrite(MOTOR_CCW_PIN, LOW);
}

void loop() {
    measureMotorPins();
    if (manualMode){
        enableManualMode();
    }

    //setRTCTimeFromSerialInput(); // Uncomment to set time

    if (COM_DEBUG.available()){
        message = COM_DEBUG.readStringUntil('.');
        char firstChar = message.charAt(0);

        // Checks if the first character is either M, B or S (Measure, Battery status, Solar status)
        switch(firstChar) {
            case 'M': 
                goToDepthAndMeasure();
                break;
            case 'B':
            case 'S':
                isAMessage = true;
                break;
            default:
                isAMessage = false;
        }
    }

    // Receives data from cannister via UART, separates it and prints on SD Card separated by comma.
    if (COM_CANNISTER.available()) {
        
        if (isAMessage){
            // Converts message to C string with '\0' at end and writes to cannister
            COM_CANNISTER.write(message.c_str()); 
            delay(500);
        }

        // Saves data received via UART from cannister to one long string
        String data = COM_CANNISTER.readStringUntil('\n');
        COM_DEBUG.print("Received data: ");
        COM_DEBUG.println(data);

        // Split data and add each data element to the global variables
        parseDataFromCannister(data);

        // Add timestamp to line on SD card
        printTimeToSD();

        // Print data to SD card
        printDataToSDCard(data);
    }
}

void goToDepthAndMeasure() {
    if (message.charAt(1) == '0') {
        
    }
}

void measureMotorPins(){
    manualMode = digitalRead(MOTOR_SWITCH_AUT);
    turnMotorCCW = digitalRead(MOTOR_BUTTON_LEFT);
    turnMotorCW = digitalRead(MOTOR_BUTTON_RIGHT);
}

// Only call when manualMode is true. Turns motor according to motor buttons pressed
void enableManualMode(){
    if (!turnMotorCCW && turnMotorCW){
        digitalWrite(MOTOR_CW_PIN, HIGH);
        digitalWrite(MOTOR_CCW_PIN, LOW);

    } else if (turnMotorCCW && !turnMotorCW){
        digitalWrite(MOTOR_CW_PIN, LOW);
        digitalWrite(MOTOR_CCW_PIN, HIGH);

    } else {
        digitalWrite(MOTOR_CW_PIN, LOW);
        digitalWrite(MOTOR_CCW_PIN, LOW);
    }
}