#pragma once
#include "modules.h"

#define maxFloats 9  // Number of sensor data that we will receive
#define SENSOR_DATA_FILENAME "results.txt"
#define depthThreshold  0.1;

/* Communication - Serial */
#define COM_DEBUG                   Serial
#define COM_DEBUG_BAUDRATE          9600

#define COM_LORA                    Serial3
#define COM_LORA_BAUDRATE           9600

#define COM_CANNISTER               Serial2
#define COM_CANNISTER_BAUDRATE      9600

// LoRa
#define CMD_TIMEOUT                 5000
#define JOIN_TIMEOUT                12000

// Depth sensor
#define ref_pressure                101325  // Pa
#define waterDensity                997     // kg/m^3
#define g_acc                       9.80665 // m/s^2

// Brake motor
#define brakeRevolution             1
#define stepsPrRevolution           3200
#define stepsToBrake                brakeRevolution*stepsPrRevolution
#define motorSpeed                  3200
#define motorAcceleration           82000