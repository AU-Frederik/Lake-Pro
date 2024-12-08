// Author: Mechatronics Group 3
// Date: 20-12-2024

#pragma once
#include "modules.h"

float receivedNumbers[MAX_FLOATS];  // Float array to hold all sensor numbers received
int floatCount;                     // Counts how many floats are received over UART
unsigned long startTime;

// For RTC
bool century = false;
bool h12Flag;
bool pmFlag;
byte year;
byte month;
byte date;
byte dow;
byte hour;
byte minute;
byte second;

// From cannister
float co2_SCD;
float avg_Humidity;
float avg_Temperature;
float pressure_HP20;
float outsideTemperature;
float CH4_sensorVolt;
float outsidePressure;
float CH4ppm;
float temperature_SCD;
float humidity_SCD;
float humidity_DHT;
float temperature_DHT;
float oxygenLevel;
int countDataReceived = 0;
bool isSensorData;

// Command and sensor data
char command;
String sensorDataString;

// Motor pins
bool manualMode = true; // Start as manual
bool automaticMode = false; 
int turnMotorCCW;
int turnMotorCW;
bool isCableBraked = true;

// Depth calculation/reaction
float depth;
bool isDestinationReached;
int destinationDepth = depthIncrements;
bool inEquilibrium;

// For calculating standard deviation of CH4 measurements
float CH4_SensorvoltHistory[NUM_VALUES] = {0};  // Buffer for last 10 values
unsigned int currentIndex = 0;                  // To track where to insert the new value
float lastStdDev = 0.0;                         // Last calculated standard deviation
float tolerance = 1.00;                         // Tolerance for checking equilibrium
