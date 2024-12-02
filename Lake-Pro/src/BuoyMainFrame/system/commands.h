#pragma once
#include "../setup/modules.h"

/**
 * @brief Delegates to other function depending on what command was called.
 * 
 */
void reactToCommand(){
    int cmd_len = command.length();

    // Checks if the first character is either M, B or S (Measure, Battery status, Solar status)
    if (command.startsWith("M") && cmd_len == 3){
        COM_DEBUG.println("Message received: M. Changing depth...");
        goToDepthAndMeasure();
    } else if (command.startsWith("B") && cmd_len == 1){
        COM_DEBUG.println("Message received: B. Measuring battery level...");
        measureBatteryStatus();
    } else if (command.startsWith("S") && cmd_len == 1){
        COM_DEBUG.println("Message received: B. Measuring solar level...");
        measureSolarStatus();
    } else {
        COM_DEBUG.println("Message doesn't start with M, B or S");
    }
}

/**
 * @brief Extracts the destination depth from the command and moves the cable motor depending on the depth now.
 * When inside the tolerance a message is sent to the cannister to start measuring.
 * 
 */
void goToDepthAndMeasure() {
    // Extracts the number part of the command and converts to an int
    String numericPart = command.substring(1);
    int destinationDepth = numericPart.toInt();

    // Variables to make code more readable
    int upperLimit = destinationDepth + depthThreshold;
    int lowerLimit = destinationDepth - depthThreshold;
    bool insideTolerance = depth < upperLimit && depth > lowerLimit;

    // If destination depth is not reached move in the correct direction
    if (depth > upperLimit && !insideTolerance){
        moveCableMotorUp();
        COM_DEBUG.println("Outside tolerance - moving up");
    } else if (depth < lowerLimit && !insideTolerance){
        moveCableMotorDown();
        COM_DEBUG.println("Outside tolerance - moving down");
    } else {
        turnOffCableMotor();
        COM_DEBUG.println("Dont know what depth to go to...");
    }

    // If destination depth is reached the cannister is told to start measuring.
    if (insideTolerance){
        COM_CANNISTER.println('M');
        COM_DEBUG.println("Inside tolerance - sending 'M' to cannister");
    } else {
        COM_CANNISTER.println('M'); // CHANGE LATER!!!
        COM_DEBUG.println("Outside tolerance - sending 'W' to cannister.");
    }
}

/**
 * @brief Does nothing right now.
 * 
 */
void measureBatteryStatus(){;}


/**
 * @brief Does nothing right now.
 * 
 */
void measureSolarStatus(){;}