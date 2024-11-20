#pragma once
#include "modules.h"

#define rxPin                   2     // Receives UART
#define txPin                   3     // Transmits UART
#define CSPin                   53    // Chip select for SD card

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
#define MOTOR_DIR_PIN           18
#define MOTOR_SLEEP_PIN         19
