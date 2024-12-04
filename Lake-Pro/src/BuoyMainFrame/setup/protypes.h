#pragma once
#include "modules.h"

// Function declaration
void    parseDataFromCannister(String);


// Control
bool    goToDepthAndMeasure(int);
void    enableManualMode();
void    reactToCommand(String);

// Motors
void    measureMotorPins();
void    moveCableMotorUp();
void    moveCableMotorDown();
void    turnOffCableMotor();
void    setupBrakeMotor();
void    brakeCable();
void    unbrakeCable();
void    shutOffBrakeMotor();
void    turnOnBrakeMotor();

// LoRa
bool    sendCommandAndReceiveResponse(const String &command, const char *expectedResponse = "OK", unsigned long timeout = 2000);
bool    LoRaConfigure();
String  stringToHex(const String&);

// Pressure sensor
float   measureRefPressure();
void    setupPressureSensor();

// RTC
void    setRTCTimeFromSerialInput();
void    showRTCTimeSettings();
void    inputDateFromSerial();

// SD
void    printDataToSDCard(String);
void    setUpSDCard();

// Battery & Solar
void    measureBatteryStatus();
void    measureSolarStatus();

// General
float   calculateDepth(float, float);
void    turnOnCannister();
void    setupCommunication();
void    runAllSetups();
void    outputDepth(float, float);
String  sendCommandToCannisterAndReceiveSensorData(char);


float calculateStandardDeviation(float*, unsigned int);
void updateCH4SensorVoltHistory(float);