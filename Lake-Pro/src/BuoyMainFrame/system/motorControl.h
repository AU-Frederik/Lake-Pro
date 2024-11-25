#pragma once
#include "../setup/modules.h"

/**
 * @brief Moves the cannister up in the water.
 * 
 */
void moveCableMotorUp(){
    digitalWrite(MOTOR_DOWN_PIN, LOW);
    digitalWrite(MOTOR_UP_PIN, HIGH);
}


/**
 * @brief Moves the cannister down in the water.
 * 
 */
void moveCableMotorDown(){
    digitalWrite(MOTOR_DOWN_PIN, HIGH);
    digitalWrite(MOTOR_UP_PIN, LOW);
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
    manualMode   = digitalRead(MOTOR_SWITCH_AUT);
    turnMotorCCW = digitalRead(MOTOR_BUTTON_LEFT);
    turnMotorCW  = digitalRead(MOTOR_BUTTON_RIGHT);
}


/**
 * @brief Only call when manualMode is true. Turns motor according to motor buttons pressed.
 * 
 */
void enableManualMode(){
    COM_DEBUG.println("Enabling manual mode...");
    if (!turnMotorCCW && turnMotorCW){
        COM_DEBUG.println("Moving cable up manually.");
        moveCableMotorUp(); // Turn CW
    } else if (turnMotorCCW && !turnMotorCW){
        COM_DEBUG.println("Moving cable down manually.");
        moveCableMotorDown();  // Turn CCW
    } else {                                  
        turnOffCableMotor();    // Don't move
    }
}

