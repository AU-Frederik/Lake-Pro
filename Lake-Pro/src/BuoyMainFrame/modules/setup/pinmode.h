#pragma once
#include "modules.h"

// Initiates all pins
void initAllPins(){
    pinMode(CSPin, OUTPUT);
    pinMode(MOTOR_DOWN_PIN,  OUTPUT);
    pinMode(MOTOR_UP_PIN,  OUTPUT);
    pinMode(MOTOR_SWITCH_AUT,   INPUT_PULLUP);
    pinMode(MOTOR_BUTTON_RIGHT, INPUT_PULLUP);
    pinMode(MOTOR_BUTTON_LEFT,  INPUT_PULLUP);
    pinMode(CannisterON_Pin, OUTPUT); // To turn on the cannister on the relay
}