#pragma once
#include "modules.h"

// Initiates all pins
void initAllPins(){
    pinMode(CSPin, OUTPUT);
    pinMode(MOTOR_CW_PIN,  OUTPUT);
    pinMode(MOTOR_CCW_PIN,  OUTPUT);
    pinMode(MOTOR_SWITCH_AUT,   INPUT_PULLUP);
    pinMode(MOTOR_BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(MOTOR_BUTTON_LEFT,  INPUT_PULLUP);
}