#pragma once
#include "../setup/modules.h"

void turnPitchUp() {
    digitalWrite(ANALOG_ROTINY_CCW, HIGH);
    digitalWrite(ANALOG_ROTINY_CW, LOW);
}

void turnPitchDown(){
    digitalWrite(ANALOG_ROTINY_CCW, LOW);
    digitalWrite(ANALOG_ROTINY_CW, HIGH);
}

void turnPitcOff(){
    digitalWrite(ANALOG_ROTINY_CCW, LOW);
    digitalWrite(ANALOG_ROTINY_CW, LOW);    
}