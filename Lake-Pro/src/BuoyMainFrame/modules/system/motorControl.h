#pragma once
#include "../setup/modules.h"

// Sets MOTOR_DOWN_PIN to LOW and MOTOR_UP_PIN to HIGH
void moveMotorUp(){
    digitalWrite(MOTOR_DOWN_PIN, LOW);
    digitalWrite(MOTOR_UP_PIN, HIGH);
}

// Sets MOTOR_DOWN_PIN to HIGH and MOTOR_UP_PIN to LOW
void moveMotorDown(){
    digitalWrite(MOTOR_DOWN_PIN, HIGH);
    digitalWrite(MOTOR_UP_PIN, LOW);
}

// Sets Rotiny motor pins to low
void holdMotor(){
    digitalWrite(MOTOR_DOWN_PIN, LOW);
    digitalWrite(MOTOR_UP_PIN, LOW);
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

