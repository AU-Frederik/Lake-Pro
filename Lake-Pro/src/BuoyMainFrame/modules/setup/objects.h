#pragma once
#include "modules.h"

// Software serial for sending UART between buoy and cannister
SoftwareSerial softSerial(rxPin, txPin);

// RTC object
DS3231 myRTC;

// File to save to on SD card
File myFile;