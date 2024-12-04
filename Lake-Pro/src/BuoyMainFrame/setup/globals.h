#pragma once
#include "modules.h"

float receivedNumbers[MAX_FLOATS]; // Float array to hold all sensor numbers received
int floatCount;                   // Counts how many floats are received over UART

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

// Calculated
float depth;

// Motor pins
int manualMode = true; // Start as manual
int turnMotorCCW;
int turnMotorCW;
bool isCableBraked = true;

bool isDestinationReached;
int destinationDepth = depthIncrements;
bool inEquilibrium;
