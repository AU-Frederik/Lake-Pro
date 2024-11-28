#pragma once
#include "modules.h"

/**
 * @brief Preheats the methane sensor for a set time. Checks every sensor iteration.
 *
 */
void initSensors(){
    // Initialize HP20x, SCD30 and DHT22 sensors
    //HP20x.begin();
    //scd30.initialize();
    dht.begin();
    

    /*
    // Sets up the ADC, BAR100 and TSYS01 sensors and holds program until they are initialized.
    while (!allSensorsReady){
        if(ads.begin()) {isADSReady = true;}
        delay(500);

        outsidePressureSensor.init();
        if(outsidePressureSensor.isInitialized()){isOutsidePressureSensorReady = true;}
        delay(500);

        if(outsideTempSensor.init()){isOutsideTempSensorReady = true;}
        delay(500);

        if (!isADSReady)                    {COM_DEBUG.println("ADC device failed to initialize!");}
        if (!isOutsidePressureSensorReady)  {COM_DEBUG.println("BAR100 device failed to initialize!");}
        if (!isOutsideTempSensorReady)      {COM_DEBUG.println("TSYS01 device failed to initialize!");}
        allSensorsReady = isADSReady && isOutsidePressureSensorReady && isOutsideTempSensorReady;
    }*/

    //COM_DEBUG.println(ads.begin());
    //outsidePressureSensor.init();
    //outsideTempSensor.init();

    // Sets gain on the ADC
    //ads.setGain(GAIN_TWOTHIRDS);

    // Sets the fluid density to fresh water
    //outsidePressureSensor.setFluidDensity(997);  
}

/**
 * @brief Preheats the methane sensor for a set time. Checks every sensor iteration.
 *
 */
bool isMethaneSensorPreheated() {
    myTime = startTime + millis(); // Time is added each iteration.
    if (myTime < timeToPreheat){
        COM_DEBUG.println("Preheating methane sensor...");
        return false;
    }
    COM_DEBUG.println("Methane sensor is now preheated.");
    return true;
}