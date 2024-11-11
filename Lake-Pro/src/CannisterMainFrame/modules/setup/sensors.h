#pragma once
#include "modules.h"

void initSensors(){
    // Initialize sensors
    HP20x.begin();
    scd30.initialize();
    dht.begin();
    
    while (!outsideTempSensor.init()) {
        Serial.println("TSYS01 device failed to initialize!");
        delay(1000);
    }
    
    while(!ads.begin()) {
        Serial.println("ADC device failed to initialize!");
        delay(1000);
    }
    ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV  0.1875mV (default)
}

void preheatMethaneSensor() {
    while (myTime < timeToPreheat){
        Serial.println("Preheating methane sensor...");
        delay(1000);
    }
    Serial.println("Methane sensor is now preheated.");
}