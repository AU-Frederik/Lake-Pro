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
KalmanFilter p_filter;    //pressure filter
DHT dht(DHT22_PIN, DHTTYPE);
Adafruit_ADS1115 ads;
TSYS01 outsideTempSensor;

/* Prototypes */
void SCD30_Measure(float*, float*, float*);
void HP20_Measure(float*);
void DHT22_Measure(float*, float*);
void outsideTemp_Measure(float*);
bool preheatMethaneSensor();
void convertCH4SensorToCH4ppm(float*);

/* Global variables */
float co2_SCD;
float humidity_SCD;
float temperature_SCD;
float humidity_DHT;
float temperature_DHT;
float pressure_HP20;
float avg_Temperature;
float avg_Humidity;
float CH4_sensorVolt;
float outsideTemperature;
float CH4ppm;
unsigned long myTime;
unsigned long minutesToPreHeat = 360;
unsigned long timeToPreheat = minutesToPreHeat * 60 * 1000; // minutes * 60 seconds/min * 1000 milliseconds/second

void setup() 
{
    // Setup I2C
    Wire.begin();
    Serial.begin(9600);

    // Setup sensors
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

    /*while (preheatMethaneSensor() != true){
        Serial.println("Preheating methane sensor...");
        delay(1000);
    }*/

    delay(1000);
}

void loop() 
{     
    dataString = "";
    // Check if SCD30 is ready
    // If yes measure CO2 in ppm, Temperature in C and Humidity in %
    if (scd30.isAvailable()) {
        SCD30_Measure(&co2_SCD, &temperature_SCD, &humidity_SCD); // passing in pointers
    }

    // Check if barometer is ready, if yes measure pressure in hPa
    if(HP20x.isAvailable()) {
        HP20_Measure(&pressure_HP20); // passing in pointer
    }

    // Measure temperature and humidity (passing in pointers)
    DHT22_Measure(&humidity_DHT, &temperature_DHT);

    // Measure outside temperature (passing in pointers)
    outsideTemp_Measure(&outsideTemperature);

    // Calculate average temperature and humidity based on the two sensors
    avg_Temperature = (temperature_DHT+temperature_SCD)/2;
    avg_Humidity = (humidity_DHT+humidity_SCD)/2;
    CH4_sensorVolt = ads.readADC_SingleEnded(0);

    convertCH4SensorToCH4ppm(&CH4ppm);

    dataString += String(co2_SCD) + ';';
    dataString += String(avg_Humidity) + ';';
    dataString += String(avg_Temperature) + ';';
    dataString += String(pressure_HP20) + ';';
    dataString += String(outsideTemperature) + ';';
    dataString += String(CH4_sensorVolt) + ';';
    dataString += String(CH4ppm);

    // Send string of sensor data with a new line
    Serial.println(dataString);

    delay(3000); //Dont change - SCD30 only works at 2.1 seconds delay or above.
}

// Measures co2, temperature and humidity on the SCD30 sensor
// given pointers to the global variables
void SCD30_Measure(float* co2, float* temperature, float* humidity)
{
    int resultLen = 3;
    // Result has CO2 on first element, Temperature on second and humidity on third
    float resultSCD[resultLen] = {0};
    scd30.getCarbonDioxideConcentration(resultSCD);
    *co2         = resultSCD[0];
    *temperature = resultSCD[1];
    *humidity    = resultSCD[2];
}

// Measures pressure on the HP20 sensor, given a pointer to the global variable
void HP20_Measure(float* pressure)
{
    long readPressure = HP20x.ReadPressure();
    *pressure = p_filter.Filter(readPressure/100.0);
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

bool preheatMethaneSensor() {
    bool isReady = false;
    myTime = millis();
    if (myTime > timeToPreheat) {
        isReady = true;
        Serial.println("Methane sensor is now preheated.");
    }
    return isReady;
}

void convertCH4SensorToCH4ppm(float* CH4ppm){
      //CH4ppm conversion
    float Pws = 0;
    float Pw = 0;
    float Vo = 0; 
    float Rs_Ro = 0;
    uint16_t Vc = 5000;  
    float g = 8.740 / pow(10,3)  ;
    float p = 129.83 ;
    float a = 3.2938 ;
    float b = -3.755 ;
    float c = 1.5718 / pow(10,6) ;
    float K = -1.4529;
    uint16_t H2Oppm = 0;

    // Define coefficients for RH to H2Oppm
    float A = 6.116441;
    float m = 7.591386;
    float Tn = 240.7263;
    uint16_t Pressure = 1013; //mbar

    Pws = A * pow(10, ((m*avg_Temperature)/(avg_Temperature+Tn)));
    Pw = avg_Humidity * Pws/100;
    H2Oppm = Pw * pow(10,6)/Pressure;
    Vo = g * H2Oppm + p;
    Rs_Ro = ((Vc/CH4_sensorVolt)-1)/((Vc/Vo)-1);
    *CH4ppm = a*pow(Rs_Ro,b) + c*(a*pow(Rs_Ro,b))*H2Oppm + K;
}