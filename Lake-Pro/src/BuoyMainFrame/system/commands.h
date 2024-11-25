#pragma once
#include "../setup/modules.h"

// Reads a command sent from the debug monitor and reacts to it
void reactToCommand(){
    // Checks if the first character is either M, B or S (Measure, Battery status, Solar status)
    if (message.startsWith("M") && message.length() == 3){
        COM_DEBUG.println("Message received: M. Changing depth...");
        goToDepthAndMeasure();
    } else if (message.startsWith("B") && message.length() == 1){
        COM_DEBUG.println("Message received: B. Measuring battery level...");
        measureBatteryStatus();
    } else if (message.startsWith("S") && message.length() == 1){
        COM_DEBUG.println("Message received: B. Measuring solar level...");
        measureSolarStatus();
    } else {
        COM_DEBUG.println("Message doesn't start with M, B or S");
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
        COM_DEBUG.println("Outside tolerance - moving up");
    } else if (depth < lowerLimit && !insideTolerance){
        moveMotorDown();
        COM_DEBUG.println("Outside tolerance - moving down");
    } else {
        holdMotor();
        COM_DEBUG.println("Dont know what depth to go to...");
    }

    if (insideTolerance){
        COM_CANNISTER.println('M');
        COM_DEBUG.println("Inside tolerance - sending 'M' to cannister");
    } else {
        COM_CANNISTER.println('W');
        COM_DEBUG.println("Outside tolerance - sending 'W' to cannister.");
    }
}

// Does nothing right now
void measureBatteryStatus(){;}
void measureSolarStatus(){;}