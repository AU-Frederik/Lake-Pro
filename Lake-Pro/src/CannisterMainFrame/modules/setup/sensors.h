#pragma once
#include "modules.h"

void initSensors(){
    // Initialize HP20x, SCD30 and DHT22 sensors
    HP20x.begin();
    scd30.initialize();
    dht.begin();
    
    // Initializes the outside temperature sensor
    while (!outsideTempSensor.init()) {
        Serial.println("TSYS01 device failed to initialize!");
        delay(1000);
    }
    
    // Initializes the ADC and sets the gain
    while(!ads.begin()) {
        Serial.println("ADC device failed to initialize!");
        delay(1000);
    }
    ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV  0.1875mV (default)

    // Initiliazes BAR100 - outside pressure sensor and sets fluid density
    /*outsidePressureSensor.init();
    while (!outsidePressureSensor.isInitialized()) {
        Serial.println("BAR100 device failed to initialize! Trying again...");
        outsidePressureSensor.init();
        delay(1000);
    }
    outsidePressureSensor.setFluidDensity(997); // kg/m^3 (freshwater, 1029 for seawater)
    */
}

void preheatMethaneSensor() {
    while (myTime < timeToPreheat){
        Serial.println("Preheating methane sensor...");
        delay(1000);
    }
    Serial.println("Methane sensor is now preheated.");
}