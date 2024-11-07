// File: CannisterMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

/*
SYSTEM RIGHT NOW CONSISTS OF: 
- DHT22 (HUMIDITY AND TEMP SENSOR)
- GROVE SCD30 (CO2, HUMIDITY AND TEMP SENSOR)
- GROVE BAROMETER (PRESSURE SENSOR INSIDE)
- TSYS01 (TEMP SENSOR IN WATER)

MISSING: 
- FIGARO NGM2611-E13 (CH4 SENSOR) THROUGH ADS1115 (ADC)
- BAR100 (OUTSIDE PRESSURE SENSOR)
*/


#include "SCD30.h"
#include <HP20x_dev.h>
#include "Arduino.h"
#include "Wire.h" 
#include <KalmanFilter.h>
#include <DHT.h>
#include <Adafruit_ADS1X15.h>
#include <TSYS01.h>

#define DHT22_PIN 12
#define DHTTYPE DHT22

String dataString;

/* Instance */
KalmanFilter t_filter;    //temperature filter
KalmanFilter p_filter;    //pressure filter
DHT dht(DHT22_PIN, DHTTYPE);
Adafruit_ADS1115 ads;
TSYS01 outsideTempSensor;

void SCD30_Measure();
void HP20_Measure();
void DHT22_Measure();
void outsideTemp_Measure();

float CO2_Measurement_SCD = 0;
float humidity_Measurement_SCD = 0;
float temperature_Measurement_SCD = 0;

float humidity_Measurement_DHT = 0;
float temperature_Measurement_DHT = 0;

float pressure_Measurement_HP20 = 0;

float average_Temperature = 0;
float average_Humidity = 0;

float CH4_Measurement = 0;

float outsideTemperature_Measurement;

void setup() {
    // Setup I2C
    Wire.begin();
    Serial.begin(9600);
    dht.begin();
    //ads.begin();
    //ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV  0.1875mV (default)

    // Setup sensors
    HP20x.begin();
    scd30.initialize();
    while (!outsideTempSensor.init()) {
        Serial.println("TSYS01 device failed to initialize!");
        delay(2000);
    }
}

void loop() {
    dataString = "";
    
    // Check if SCD30 is ready
    // If yes send CO2 in ppm, Temperature in C and Humidity in % to AIB
    if (scd30.isAvailable()) {
        SCD30_Measure();
    }

    // Check if barometer is ready, if yes send pressure in hPa to AIB
    if(HP20x.isAvailable()) {
        HP20_Measure();
    }

    // Measure temperature and humidity
    DHT22_Measure();
    outsideTemp_Measure();

    average_Temperature = (temperature_Measurement_DHT+temperature_Measurement_SCD)/2;
    average_Humidity = (humidity_Measurement_DHT+humidity_Measurement_SCD)/2;
    //CH4_Measurement = ads.readADC_SingleEnded(0);

    dataString += String(CO2_Measurement_SCD) + ';';
    dataString += String(average_Humidity) + ';';
    dataString += String(average_Temperature) + ';';
    dataString += String(pressure_Measurement_HP20) + ';';
    dataString += String(outsideTemperature_Measurement) + ';';
    //dataString += String(CH4_Measurement);

    // Send string of sensor data with a new line
    Serial.println(dataString);

    delay(3000); //Dont change - SCD30 only works at 2.1 seconds delay or above.
}

void SCD30_Measure(){
    int resultLen = 3;
    // Result has CO2 on first element, Temperature on second and humidity on third
    float resultSCD[resultLen] = {0};
    scd30.getCarbonDioxideConcentration(resultSCD);
    CO2_Measurement_SCD         = resultSCD[0];
    temperature_Measurement_SCD = resultSCD[1];
    humidity_Measurement_SCD    = resultSCD[2];
}

void HP20_Measure()
{
    long Pressure = HP20x.ReadPressure();
    pressure_Measurement_HP20 = Pressure/100.0;
}

void DHT22_Measure(){
    humidity_Measurement_DHT    = dht.readHumidity();
    temperature_Measurement_DHT = dht.readTemperature();
}

void outsideTemp_Measure(){
    outsideTempSensor.read();
    outsideTemperature_Measurement = outsideTempSensor.temperature();
}