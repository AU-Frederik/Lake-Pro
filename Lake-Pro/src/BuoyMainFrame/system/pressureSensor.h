#pragma once
#include "../setup/modules.h"

// Measures pressure on the HP20 sensor, given a pointer to the global variable
void measureRefPressure(float* pressure) {
    COM_DEBUG.println("Measuring reference pressure");
    if(HP20x.isAvailable()) {
        long readPressure = HP20x.ReadPressure();
        *pressure = p_filter.Filter(readPressure/100.0);
    }
}

void setupPressureSensor() {
    HP20x.begin();
}