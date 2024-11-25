#pragma once
#include "../setup/modules.h"

// Measures pressure on the HP20 sensor, given a pointer to the global variable
/**
 * @brief Measures the reference pressure using the HP20x sensor.
 * @param pressure a float pointer to the global variable.
 */
void measureRefPressure(float* pressure) {
    COM_DEBUG.println("Measuring reference pressure");
    if(HP20x.isAvailable()) {
        long readPressure = HP20x.ReadPressure();
        *pressure = p_filter.Filter(readPressure/100.0);
    }
}


/**
 * @brief Initializes the reference pressure sensor HP20x.
 * 
 */
void setupPressureSensor() {
    HP20x.begin();
}