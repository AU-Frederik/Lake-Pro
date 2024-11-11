#pragma once
#include "../setup/modules.h"

void measureAll(){
    // measure CO2 in ppm, Temperature in C and Humidity in %
    SCD30_Measure(&co2_SCD, &temperature_SCD, &humidity_SCD);

    // Check if barometer is ready, if yes measure pressure in hPa
    HP20_Measure(&pressure_HP20);

    // Measure temperature and humidity
    DHT22_Measure(&humidity_DHT, &temperature_DHT);

    // Measure outside temperature
    outsideTemp_Measure(&outsideTemperature);

    // Measures pressure outside and calculates depth (inside the reference pressure can be calculated differently)
    outsidePressureAndDepth_Measure(&outsidePressure, &depth);

    // Measure CH4
    CH4_Measure(&CH4_sensorVolt);

    calculateAverageTempAndHumidity(&avg_Temperature, &avg_Humidity);
    convertCH4SensorToCH4ppm(&CH4ppm);
}

// Measures CO2, temperature and humidity on the SCD30 sensor
void SCD30_Measure(float* co2, float* temperature, float* humidity)
{
    int resultLen = 3;
    // Result has CO2 on first element, Temperature on second and humidity on third
    float resultSCD[resultLen] = {0};

    if (scd30.isAvailable()) {
        scd30.getCarbonDioxideConcentration(resultSCD);
        *co2         = resultSCD[0];
        *temperature = resultSCD[1];
        *humidity    = resultSCD[2];
    }
}

// Measures pressure on the HP20 sensor, given a pointer to the global variable
void HP20_Measure(float* pressure)
{
    if(HP20x.isAvailable()) {
        long readPressure = HP20x.ReadPressure();
        *pressure = p_filter.Filter(readPressure/100.0);
    } else {
        *pressure = 0;
    }
}

// Measures humidity and temperature on the DHT22 sensor, given pointers to the global variables
void DHT22_Measure(float* humidity, float* temperature) 
{
    float h   = dht.readHumidity();
    float t   = dht.readTemperature();

    *humidity = isnan(h) ? 0.0 : h;  // fallback to 0.0 if NaN
    *temperature = isnan(t) ? 0.0 : t;  // fallback to 0.0 if NaN
}

// Measures outside temperature on the TSYS01 sensor, given a pointer to the global variable
void outsideTemp_Measure(float* temperature)
{
    outsideTempSensor.read();
    float t = outsideTempSensor.temperature();
    *temperature = isnan(t) ? 0.0 : t;  // fallback to 0.0 if NaN
}

// Measures the sensor volt from the ADC connected to the Figaro sensor
void CH4_Measure(float* CH4){
    CH4_sensorVolt = ads.readADC_SingleEnded(0);
}

// Measures the outside pressure and calculates the depth
void outsidePressureAndDepth_Measure(float* pressure, float* depth) {
    outsidePressureSensor.read();
    *pressure = outsidePressureSensor.pressure();

    // Calculates the depth (change ref_pressure to buoy pressure)
    float ref_pressure = 101325;    // Pa
    float fluidDensity = 997;       // kg/m^3
    float g_acc        = 9.80665;   // m/s^2
    *depth = (*pressure-ref_pressure)/(fluidDensity*g_acc);
}



