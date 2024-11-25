#pragma once
#include "modules.h"

// Initiates all pins
void initAllPins(){
    pinMode(CSPin, OUTPUT);
    pinMode(CannisterON_Pin, OUTPUT); // To turn on the cannister on the relay

    // Rotiny motor pins for cable winch
    pinMode(MOTOR_DOWN_PIN,  OUTPUT);
    pinMode(MOTOR_UP_PIN,  OUTPUT);

    // Input from buttons
    pinMode(MOTOR_SWITCH_AUT,   INPUT_PULLUP);
    pinMode(MOTOR_BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(MOTOR_BUTTON_LEFT,  INPUT_PULLUP);

    // Stepper motor for brake
    pinMode(MOTOR_DIR_PIN, OUTPUT);
    pinMode(MOTOR_SLEEP_PIN,  OUTPUT);
    pinMode(MOTOR_STEP_PIN,  OUTPUT);
}

void turnOnCannister(){
    digitalWrite(CannisterON_Pin, HIGH);
}