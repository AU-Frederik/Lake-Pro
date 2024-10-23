// File: CannisterMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

#include "SCD30.h"
#include <HP20x_dev.h>
#include "Arduino.h"
#include "Wire.h" 
#include <KalmanFilter.h>

/* Instance */
KalmanFilter t_filter;    //temperature filter
KalmanFilter p_filter;    //pressure filter

void sendSCDResult();
void sendHP20Result();

void setup() {
    // Setup I2C
    Wire.begin();
    Serial.begin(9600);

    // Setup sensors
    HP20x.begin();
    scd30.initialize();
}

void loop() {
    
    // Check if SCD30 is ready
    // If yes send CO2 in ppm, Temperature in C and Humidity in % to AIB
    if (scd30.isAvailable()) {
        sendSCDResult();
    }

    // Check if barometer is ready, if yes send pressure in hPa to AIB
    if(HP20x.isAvailable()) {
      sendHP20Result();
    }

    delay(3000); //Dont change - SCD30 only works at 2 seconds delay
}

void sendSCDResult(){
    // Result has CO2 on first element, Temperature on second and humidity on third
    float resultSCD[3] = {0};
    scd30.getCarbonDioxideConcentration(resultSCD);
    Serial.print(resultSCD[0]); Serial.print(";");
    Serial.print(resultSCD[1]); Serial.print(";");
    Serial.print(resultSCD[2]); Serial.print(";");
}

void sendHP20Result()
{
    long Pressure = HP20x.ReadPressure();
    float p = Pressure/100.0;
    Serial.print(p); Serial.println("");
}