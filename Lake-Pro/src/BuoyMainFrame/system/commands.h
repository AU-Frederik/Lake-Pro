#pragma once
#include "../setup/modules.h"

/**
 * @brief Delegates to other function depending on what command was called.
 * 
 */
void reactToCommand(String commandReceivedFromLora){
    int cmd_len = commandReceivedFromLora.length();

    // Checks if the first character is either M, B or S (Measure, Battery status, Solar status)
    if (commandReceivedFromLora.startsWith("M") && cmd_len == 3){
        DEBUG_SERIAL.println("Message received: M. Changing depth...");
        String numericPart = commandReceivedFromLora.substring(1);
        int maxDepth = numericPart.toInt(); // 10
        DEBUG_SERIAL.print("Max depth: ");
        DEBUG_SERIAL.println(maxDepth);
        
        if (!isDestinationReached){
            isDestinationReached = goToDepthAndMeasure(destinationDepth);
        } else if (isDestinationReached && destinationDepth < maxDepth){
            destinationDepth += depthIncrements;
        } else if (isDestinationReached && destinationDepth >= maxDepth){
            destinationDepth = depthIncrements;
        }
    
    } else if (commandReceivedFromLora.startsWith("B") && cmd_len == 1){
        DEBUG_SERIAL.println("Message received: B. Measuring battery level...");
        measureBatteryStatus();
    } else if (commandReceivedFromLora.startsWith("S") && cmd_len == 1){
        DEBUG_SERIAL.println("Message received: B. Measuring solar level...");
        measureSolarStatus();
    } else {
        DEBUG_SERIAL.println("Message doesn't start with M, B or S");
    }
}

/**
 * @brief Extracts the destination depth from the command and moves the cable motor depending on the depth now.
 * When inside the tolerance a message is sent to the cannister to start measuring.
 * 
 */
bool goToDepthAndMeasure(int destinationDepth) {
    // Variables to make code more readable
    int upperLimit = destinationDepth + DEPTH_THRESHOLD; // Depth_threshold is in meters
    int lowerLimit = destinationDepth - DEPTH_THRESHOLD;
    bool insideTolerance = depth < upperLimit && depth > lowerLimit;

    // If destination depth is not reached move in the correct direction
    if (depth > upperLimit && !insideTolerance){
        moveCableMotorUp();
        DEBUG_SERIAL.println("Outside tolerance - moving up");
    } else if (depth < lowerLimit && !insideTolerance){
        moveCableMotorDown();
        DEBUG_SERIAL.println("Outside tolerance - moving down");
    } else {
        turnOffCableMotor();
        DEBUG_SERIAL.println("Dont know what depth to go to...");
    }

    // If destination depth is reached the cannister is told to start measuring.
    if (insideTolerance){
        CANNISTER_SERIAL.println('M');
        DEBUG_SERIAL.println("Inside tolerance - sending 'M' to cannister");
        brakeCable(STEPS_TO_BRAKE);
        return true;
    } else {
        CANNISTER_SERIAL.println('M'); // CHANGE LATER!!!
        DEBUG_SERIAL.println("Outside tolerance - sending 'W' to cannister.");
        return false;
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