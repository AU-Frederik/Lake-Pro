#pragma once
#include "modules.h"

float receivedNumbers[maxFloats]; // Float array to hold all sensor numbers received
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
float depth;
float CH4ppm;

// Motor pins
int manualMode;
int turnMotorCCW;
int turnMotorCW;

// Commands
String message;