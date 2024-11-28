#pragma once
#include "modules.h"

// Chip select for SD card
#define CSPin                   53

// Motor pins for Rotiny moving the winch
#define MOTOR_DOWN_PIN          10
#define MOTOR_UP_PIN            8
#define MOTOR_SWITCH_AUT        3    
#define MOTOR_BUTTON_RIGHT      5
#define MOTOR_BUTTON_LEFT       4

// Turns on the cannister on the PCB
#define CannisterON_Pin         6

// Motor pins for Brake stepper motor
#define MOTOR_STEP_PIN          2
#define MOTOR_DIR_PIN           19
#define MOTOR_SLEEP_PIN         18

// Battery
#define PA_SENSOR_BATT          A0