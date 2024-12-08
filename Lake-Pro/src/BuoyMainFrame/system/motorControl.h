// Author: Mechatronics Group 3
// Date: 20-12-2024

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
 * @brief Measures the two manual buttons on the winch.
 * 
 */
void checkMotorButtons(){
    turnMotorCCW = digitalRead(MOTOR_BUTTON_DOWN);
    turnMotorCW  = digitalRead(MOTOR_BUTTON_UP);
    
    // If both buttons are pressed in the system changes mode.
    if (!turnMotorCCW && !turnMotorCW) {
        delay(1500);
        if (manualMode){
            manualMode = false;
            automaticMode = true;
            DEBUG_SERIAL.println("Changing to Automatic mode!");
        } else {
            manualMode = true;
            automaticMode = false;
            isCableBraked = true;           // For the unbrakeCable function to work
            unbrakeCable(STEPS_TO_BRAKE);   // Unbrakes before manual mode is set
            DEBUG_SERIAL.println("Changing to Manual mode!");
        }
    }

    // Moves the motor according to button pressed
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
