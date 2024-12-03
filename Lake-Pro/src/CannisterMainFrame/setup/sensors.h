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
        DEBUG_SERIAL.println("Preheating methane sensor...");
        return false;
    }
    DEBUG_SERIAL.println("Methane sensor is now preheated.");
    return true;
}

/**
 * @brief Method sets all sensor booleans to false and proceeds to check all sensors initiliazation. Initializes if they are not already initialized.
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




    // Prints availability of the sensors
    DEBUG_SERIAL.print("HP20x: "   );      DEBUG_SERIAL.print(isHP20xReady  ? "Ready" : "Not ready");
    DEBUG_SERIAL.print(", SCD30: " );      DEBUG_SERIAL.print(isSCD30Ready  ? "Ready" : "Not ready");
    DEBUG_SERIAL.print(", BAR100: ");      DEBUG_SERIAL.print(isBAR100Ready ? "Ready" : "Not ready");
    DEBUG_SERIAL.print(", ADS: "   );      DEBUG_SERIAL.println(isADSReady  ? "Ready" : "Not ready");
}