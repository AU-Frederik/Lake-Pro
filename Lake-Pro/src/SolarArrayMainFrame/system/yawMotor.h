#pragma once
#include "../setup/modules.h"


/**
 * @brief Moves the yaw motor in a clock-wise rotation at max speed.
 * 
 */
void turnYawCW() {
    analogWrite(YAW_ENABLE_PIN, YAW_MAX_SPEED);
    digitalWrite(YAW_MOTOR_PIN1, HIGH);
    digitalWrite(YAW_MOTOR_PIN2, LOW);
}

/**
 * @brief Moves the yaw motor in a counter clock-wise rotation at max speed.
 * 
 */
void turnYawCCW() {
    analogWrite(YAW_ENABLE_PIN, YAW_MAX_SPEED);
    digitalWrite(YAW_MOTOR_PIN1, LOW);
    digitalWrite(YAW_MOTOR_PIN2, HIGH);
}

/**
 * @brief Turns of the yaw motor by ramping it down in speed.
 * 
 */
void turnYawOff() {
    for (int speed = YAW_MAX_SPEED; speed > 0; speed--) {
        analogWrite(YAW_ENABLE_PIN, speed);
        delay(YAW_ACC);
    }

    digitalWrite(YAW_MOTOR_PIN1, LOW);
    digitalWrite(YAW_MOTOR_PIN2, LOW);
}