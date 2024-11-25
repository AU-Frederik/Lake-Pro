#pragma once
#include "../setup/modules.h"

/**
 * @brief Points the solar array upwards.
 * 
 */
void turnPitchUp() {
    digitalWrite(ANALOG_ROTINY_CCW, HIGH);
    digitalWrite(ANALOG_ROTINY_CW, LOW);
}

/**
 * @brief Points the solar array downwards.
 * 
 */
void turnPitchDown(){
    digitalWrite(ANALOG_ROTINY_CCW, LOW);
    digitalWrite(ANALOG_ROTINY_CW, HIGH);
}

/**
 * @brief Turns pitch motor off.
 * 
 */
void turnPitchOff(){
    digitalWrite(ANALOG_ROTINY_CCW, LOW);
    digitalWrite(ANALOG_ROTINY_CW, LOW);    
}