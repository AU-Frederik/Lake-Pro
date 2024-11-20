#pragma once
#include "modules.h"

// Software serial for sending UART between buoy and cannister
SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);

// RTC object
DS3231 myRTC;

// File to save to on SD card
File myFile;

// Stepper motor for brake
// set up the accelStepper intance
// the "1" tells it we are using a driver
AccelStepper stepper(1, MOTOR_STEP_PIN, MOTOR_DIR_PIN);