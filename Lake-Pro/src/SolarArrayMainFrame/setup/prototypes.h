#pragma once
#include "modules.h"

// LDR sensors
void readLDRSensors();
void outputLDRValues();

// Yaw/DC motor
void turnYawCW();
void turnYawCCW();
void turnYawOff();

// Rotiny/Pitch motor
void turnPitchUp();
void turnPitchDown();
void turnPitchOff();

// Calibration
void calibratePosition();