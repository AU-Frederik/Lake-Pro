#pragma once
#include "modules.h"

// Motor and H-bridge pins
#define YAW_ENABLE_PIN      6   // Needs to support PWM channel
#define YAW_MOTOR_PIN1      7
#define YAW_MOTOR_PIN2      8

// Rotiny
#define ANALOG_ROTINY_CCW   A0
#define ANALOG_ROTINY_CW    A1

// LDR constants
#define LDR_NORTH_PIN       A7
#define LDR_SOUTH_PIN       A6
#define LDR_EAST_PIN        A2
#define LDR_WEST_PIN        A3
