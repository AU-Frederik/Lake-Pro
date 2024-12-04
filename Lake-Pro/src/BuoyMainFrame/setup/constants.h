#pragma once
#include "modules.h"

#define MAX_FLOATS                  9  // Number of sensor data that we will receive
#define NUM_VALUES                  10 // Amount of CH4 sensor volts to calculate the standard deviation from.
#define SENSOR_DATA_FILENAME        "results.txt"
#define DEPTH_THRESHOLD             0.1

/* Communication - Serial */
#define DEBUG_SERIAL                Serial
#define DEBUG_SERIAL_BAUDRATE       9600

#define COM_LORA                    Serial3
#define COM_LORA_BAUDRATE           9600

#define CANNISTER_SERIAL            Serial2
#define CANNISTER_SERIAL_BAUDRATE   9600

// LoRa
#define CMD_TIMEOUT                 5000
#define JOIN_TIMEOUT                12000

// Depth sensor
#define REF_PRESSURE                101325  // Pa
#define WATER_DENSITY               997     // kg/m^3
#define G_ACC                       9.80665 // m/s^2

// Brake motor
#define BRAKE_REVOLUTION            1
#define STEPS_PR_REVOLUTION         3200
#define STEPS_TO_BRAKE              BRAKE_REVOLUTION*STEPS_PR_REVOLUTION
#define MOTOR_SPEED                 3200
#define MOTOR_ACCELERATION          82000

// Battery
// BatteryReading = 3 kOhm / (3 kOhm + 9 kOhm) * Battery Voltage
// 12.6V .. 10.5V -> ~3.15V .. 2.65V -> 645 .. 542
#define BATTERY_VOLTAGE_MIN         10.7f
#define BATTERY_VOLTAGE_MAX         12.6f
#define BATTERY_SCALE_A             28.722f
#define BATTERY_SCALE_B             -617.39f
#define BATTERY_OFFSET              3318.3f
#define BATTERY_VOLTAGE_OFFSET      0.1f