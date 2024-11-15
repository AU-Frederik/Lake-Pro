#pragma once
#include "modules.h"

// Function declaration
void parseDataFromCannister();
void setRTCTimeFromSerialInput();
void showRTCTimeSettings();
void inputDateFromSerial();
void printTime();
void printDataToSDCard(String);
void setUpSDCard();
void goToDepthAndMeasure();
void measureMotorPins();
void enableManualMode();