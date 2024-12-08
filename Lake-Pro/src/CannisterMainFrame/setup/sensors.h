// Author: Mechatronics Group 3
// Date: 20th of December, 2024

#pragma once
#include "modules.h"

/**
 * @brief Preheats the methane sensor for a set time. Checks every sensor iteration.
 *
 */
void initAllSensors() {
    BAR100.init();
    
    dht22.begin();

    if (ads.begin()) { 
        ads.setGain(GAIN_TWOTHIRDS);
        isADSReady = true;
    }
}

/**
 * @brief Preheats the methane sensor for a set time. Checks every sensor iteration.
 *
 */
bool isMethaneSensorPreheated() {
    myTime = setupTime + millis(); // Time is added each iteration.
    if (myTime < TIME_TO_PREHEAT){
        return false;
    }
    return true;
}

/**
 * @brief Checks all sensors initiliazation. Initializes if they are not already initialized.
 * 
 */
void checkInitializationOfSensors(){
    if (HP20x.isAvailable()){
        isHP20xReady = true;
    } else {
        HP20x.begin();
    }

    if (scd30.isAvailable()){
        isSCD30Ready = true;
    } else {
        scd30.initialize();
    }

    if (BAR100.isInitialized()){
        isBAR100Ready = true;
        BAR100.setFluidDensity(FRESH_WATER_DENSITY);
    } else {
        BAR100.init();
        BAR100.setFluidDensity(FRESH_WATER_DENSITY);
    }
}