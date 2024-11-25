#pragma once

// Libraries
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <DS3231.h>
#include <AccelStepper.h>
#include <HP20x_dev.h>
#include <KalmanFilter.h>

// Setup files - do not change the order!
#include "constants.h"
#include "globals.h"
#include "pinout.h"
#include "objects.h"
#include "protypes.h"
#include "pinmode.h"
#include "communication.h"

// System files
#include "../system/rtc.h"
#include "../system/sd.h"
#include "../system/dataParser.h"
#include "../system/motorControl.h"
#include "../system/commands.h"
#include "../system/brake.h"
#include "../system/lora.h"
#include "../system/pressureSensor.h"