#pragma once
#include "modules.h"

void initAllPins(){
    //LDR Pin setup
    pinMode(LDR_NORTH_PIN,INPUT);
    pinMode(LDR_SOUTH_PIN,INPUT);
    pinMode(LDR_EAST_PIN,INPUT);
    pinMode(LDR_WEST_PIN,INPUT);

    //Motor and Hbridge Pin setup
    pinMode(YAW_ENABLE_PIN, OUTPUT); //default 8-bit resolution
    pinMode(YAW_MOTOR_PIN1, OUTPUT);
    pinMode(YAW_MOTOR_PIN2, OUTPUT);

    //Rotiny setup
    pinMode(ANALOG_ROTINY_CCW, OUTPUT);
    pinMode(ANALOG_ROTINY_CW, OUTPUT);
}