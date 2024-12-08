#pragma once
#include "../setup/modules.h"

/**
 * @brief Moves the cannister up in the water.
 * 
 */
void moveCableMotorUp(){
    digitalWrite(MOTOR_DOWN_PIN, HIGH);
    digitalWrite(MOTOR_UP_PIN, LOW);
}


/**
 * @brief Moves the cannister down in the water.
 * 
 */
void moveCableMotorDown(){
    digitalWrite(MOTOR_DOWN_PIN, LOW);
    digitalWrite(MOTOR_UP_PIN, HIGH);
}

/**
 * @brief Turns off the cable motor.
 * 
 */
void turnOffCableMotor(){
    digitalWrite(MOTOR_DOWN_PIN, LOW);
    digitalWrite(MOTOR_UP_PIN, LOW);
}

/**
 * @brief Measures the three manual buttons on the winch.
 * 
 */
void measureMotorPins(){
    turnMotorCCW = digitalRead(MOTOR_BUTTON_DOWN);
    turnMotorCW  = digitalRead(MOTOR_BUTTON_UP);
    
    if (!turnMotorCCW && !turnMotorCW) {
        delay(1500);
        if (manualMode){
            manualMode = false;
            DEBUG_SERIAL.println("Changing to Automatic mode!");
        } else {
            manualMode = true;
            isCableBraked = true;
            unbrakeCable(STEPS_TO_BRAKE);
            DEBUG_SERIAL.println("Changing to Manual mode!");
        }
    }
    else if (!turnMotorCW && turnMotorCCW && manualMode) {
        moveCableMotorUp();
    }
    else if (turnMotorCW && !turnMotorCCW && manualMode) {
        moveCableMotorDown();
    }
    else if (turnMotorCW && turnMotorCCW && manualMode) {
        turnOffCableMotor();
    }
}


/**
 * @brief Only call when manualMode is true. Turns motor according to motor buttons pressed.
 * 
 */
void enableManualMode(){
    if (!turnMotorCCW && turnMotorCW){
        moveCableMotorDown(); // Turn CCW
        DEBUG_SERIAL.println("Moving cannister down");
    } else if (turnMotorCCW && !turnMotorCW){
        moveCableMotorUp();  // Turn CW
        DEBUG_SERIAL.println("Moving cannister up");
    } else {                                  
        turnOffCableMotor();    // Don't move
    }
}

