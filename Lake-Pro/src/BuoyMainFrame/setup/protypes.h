// Author: Mechatronics Group 3
// Date: 20-12-2024

#pragma once
#include "modules.h"

// Function declaration
void    parseDataFromCannister(String);

// Control
bool    goToDepthAndMeasure(int);
void    reactToCommand(String);

// Motors
void    checkMotorButtons();
void    moveCableMotorUp();
void    moveCableMotorDown();
void    turnOffCableMotor();
void    setupBrakeMotor();
void    brakeCable(long);
void    unbrakeCable(long);
void    shutOffBrakeMotor();
void    turnOnBrakeMotor();

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
void    printBatteryLevel();

// General
float   calculateAndOutputDepth(float, float);
void    turnOnCannister();
void    setupCommunication();
void    outputDepth(float, float);
String  sendCommandToCannisterAndReceiveSensorData(char);
void    parseDataAndSaveToSDCard(String dataString);

// For CH4 equilibrium measurements
float calculateStandardDeviation(float*, unsigned int);
void updateCH4SensorVoltHistory(float);