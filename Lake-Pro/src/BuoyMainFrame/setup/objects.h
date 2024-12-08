// Author: Mechatronics Group 3
// Date: 20-12-2024

#pragma once
#include "modules.h"

// RTC object
DS3231 myRTC;

// File to save to on SD card
File myFile;

// Set up the accelStepper instance. The "1" tells it, that we are using a driver
AccelStepper stepper(1, MOTOR_STEP_PIN, MOTOR_DIR_PIN);

// Filter reference pressure sensor data
KalmanFilter p_filter;