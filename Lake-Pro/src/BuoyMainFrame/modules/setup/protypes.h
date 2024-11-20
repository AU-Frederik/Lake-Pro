#pragma once
#include "modules.h"

// Function declaration
void parseDataFromCannister(String);
void setRTCTimeFromSerialInput();
void showRTCTimeSettings();
void inputDateFromSerial();
void printTime();
void printDataToSDCard(String);
void setUpSDCard();
void goToDepthAndMeasure();
void measureMotorPins();
void enableManualMode();
void reactToCommand();
void receiveFromUARTAndPrintToSDCard();
void measureBatteryStatus();
void measureSolarStatus();
void moveMotorUp();
void moveMotorDown();
void holdMotor();
void calculateDepth();