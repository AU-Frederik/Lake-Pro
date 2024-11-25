#pragma once
#include "../setup/modules.h"

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

    // Checks if the first character is either M, B or S (Measure, Battery status, Solar status)
    if (message.startsWith("M") && message.length() == 3){
        goToDepthAndMeasure();
    } else if (message.startsWith("B") && message.length() == 1){
        measureBatteryStatus();
    } else if (message.startsWith("S") && message.length() == 1){
        measureSolarStatus();
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

// Does nothing right now
void measureBatteryStatus(){;}
void measureSolarStatus(){;}