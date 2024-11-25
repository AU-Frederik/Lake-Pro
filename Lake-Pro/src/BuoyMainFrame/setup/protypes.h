#pragma once
#include "modules.h"

// Function declaration
void parseDataFromCannister(String);

// Data parsing
void receiveFromUARTAndPrintToSDCard();

// Control
void goToDepthAndMeasure();
void enableManualMode();
void reactToCommand();

// Motors
void measureMotorPins();
void moveCableMotorUp();
void moveCableMotorDown();
void turnOffCableMotor();
void setupBrakeMotor();
void brakeCable();
void unbrakeCable();
void shutOffBrakeMotor();
void turnOnBrakeMotor();

// LoRa
bool sendCommandAndReceiveResponse(const String &command, const char *expectedResponse = "OK", unsigned long timeout = 2000);
bool LoRaConfigure();
String stringToHex(const String&);

// Pressure sensor
void measureRefPressure(float*);
void setupPressureSensor();

// RTC
void setRTCTimeFromSerialInput();
void showRTCTimeSettings();
void inputDateFromSerial();

// SD
void printDataToSDCard(String);
void setUpSDCard();

// Battery & Solar
void measureBatteryStatus();
void measureSolarStatus();

// General
void calculateDepth();
void turnOnCannister();