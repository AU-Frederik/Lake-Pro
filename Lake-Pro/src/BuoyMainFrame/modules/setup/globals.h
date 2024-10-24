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