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
void setupBrakeMotor();
void brakeCable();
void unbrakeCable();
void shutOffBrakeMotor();
void turnOnBrakeMotor();
void setMotorDirection(int);
void turnOnCannister();
bool sendCommandAndReceiveResponse(const String &command, const char *expectedResponse = "OK", unsigned long timeout = 2000);
bool LoRaConfigure();
String stringToHex(const String&);
void measureRefPressure(float*);
void setupPressureSensor();