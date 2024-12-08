// Author: Mechatronics Group 3
// Date: 20-12-2024

#pragma once
#include "../setup/modules.h"

/**
 * @brief Measures the reference pressure using the HP20x sensor.
 * @param pressure a float pointer to the global variable.
 */
float measureRefPressure() {
    float pressure = 0;
    if(HP20x.isAvailable()) {
        long readPressure = HP20x.ReadPressure();
        pressure = p_filter.Filter(readPressure/100.0);
    }
    return pressure;
}


/**
 * @brief Initializes the reference pressure sensor HP20x.
 * 
 */
void setupPressureSensor() {
    HP20x.begin();
}