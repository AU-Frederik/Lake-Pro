#pragma once
#include "../setup/modules.h"

void turnYawCW() {
    // temporary speed control, should use LDR readings once properly mapped
    digitalWrite(YAW_MOTOR_PIN1, HIGH);
    digitalWrite(YAW_MOTOR_PIN2, LOW);

    for (int speed = 0; speed < YAW_MAX_SPEED; speed++) {
        analogWrite(YAW_ENABLE_PIN,speed);
        delay(15);
    }
}

void turnYawCCW() {
    // temporary speed control, should use LDR readings once properly mapped
    digitalWrite(YAW_MOTOR_PIN1, LOW);
    digitalWrite(YAW_MOTOR_PIN2, HIGH);

    for (int speed = 0; speed < YAW_MAX_SPEED; speed++) {
        analogWrite(YAW_ENABLE_PIN, speed);
        delay(15);
    }
}

void turnYawOff() {
    for (int speed = YAW_MAX_SPEED; speed > 0; speed--) {
        analogWrite(YAW_ENABLE_PIN, speed);
        delay(15);
    }

    digitalWrite(YAW_MOTOR_PIN1, LOW);
    digitalWrite(YAW_MOTOR_PIN2, LOW);
}