#pragma once
#include "modules.h"

// Sets up the different communication ways
void setupCommunication(){
    Wire.begin();               // I2C 
    Serial.begin(9600);         // For printing to monitor
    Serial1.begin(9600);
}