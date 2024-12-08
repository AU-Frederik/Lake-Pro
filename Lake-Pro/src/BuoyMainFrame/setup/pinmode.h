// Author: Mechatronics Group 3
// Date: 20-12-2024

#pragma once
#include "modules.h"

/**
* @brief Sets pin mode on all pins.
* 
*/
void initAllPins(){
    pinMode(CSPin, OUTPUT);
    pinMode(CannisterON_Pin, OUTPUT); // To turn on the cannister on the relay

    // Rotiny motor pins for cable winch
    pinMode(MOTOR_DOWN_PIN,  OUTPUT);
    pinMode(MOTOR_UP_PIN,  OUTPUT);

    // Input from buttons
    pinMode(MOTOR_SWITCH_AUT,   INPUT_PULLUP);
    pinMode(MOTOR_BUTTON_UP, INPUT_PULLUP);
    pinMode(MOTOR_BUTTON_DOWN,  INPUT_PULLUP);

    // Stepper motor for brake
    pinMode(MOTOR_SLEEP_PIN,  OUTPUT);

    // Reads on battery analog
    pinMode(PA_SENSOR_BATT, INPUT);
}

/**
 * @brief Turns on the cannister on the PCB pin.
 * 
 */
void turnOnCannister(){
    digitalWrite(CannisterON_Pin, HIGH);
}