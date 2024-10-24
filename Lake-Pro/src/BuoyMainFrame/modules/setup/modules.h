#pragma once

// Libraries
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <DS3231.h>

// Setup files - do not change the order!
#include "constants.h"
#include "globals.h"
#include "pinout.h"
#include "objects.h"
#include "protypes.h"


// System files
#include "../system/rtc.h"
#include "../system/sd.h"
#include "../system/dataParser"