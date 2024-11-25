#pragma once
#include "modules.h"

// RTC object
DS3231 myRTC;

// File to save to on SD card
File myFile;

// set up the accelStepper instance. The "1" tells it, that we are using a driver
AccelStepper stepper(1, MOTOR_STEP_PIN, MOTOR_DIR_PIN);

// Used to filter reference pressure sensor data
KalmanFilter p_filter;