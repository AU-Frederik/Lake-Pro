#pragma once
#include "../setup/modules.h"

/**
 * @brief Sets max speed and acceleration of the brake motor.
 * 
 */
void setupBrakeMotor(){
    stepper.setMaxSpeed(motorSpeed);
    stepper.setAcceleration(motorAcceleration);
}

/**
 * @brief Turns on the brake motor, brakes the cable if the cable is not already braked and shuts it off again.
 * 
 */
void brakeCable() {
    if (isCableBraked) return;
    turnOnBrakeMotor();
    stepper.setCurrentPosition(0); // Reset the current position to 0
    stepper.moveTo(-stepsToBrake);   // Move the stepper motor down

    while (stepper.distanceToGo() != 0) { // Check remaining steps to avoid blocking loops
        stepper.run();
    }

    shutOffBrakeMotor(); // Turn off motor if holding torque isn't required
    isCableBraked = true;
}

/**
 * @brief Turns on the brake motor, unbrakes the cable if the cable is braked and shuts it off again.
 * 
 */
void unbrakeCable() {
    if (!isCableBraked) return;
    turnOnBrakeMotor();
    stepper.setCurrentPosition(0); // Reset the current position to 0
    stepper.move(stepsToBrake);    // Move the stepper motor up

    while (stepper.distanceToGo() != 0) { // Check remaining steps to avoid blocking loops
        stepper.run();
    }

    shutOffBrakeMotor(); // Turn off motor if holding torque isn't required
    isCableBraked = false;
}

/**
 * @brief Turns on the brake motor.
 * 
 */
void turnOnBrakeMotor(){
    digitalWrite(MOTOR_SLEEP_PIN, HIGH);
}

/**
 * @brief Shuts off the brake motor.
 * 
 */
void shutOffBrakeMotor(){
    digitalWrite(MOTOR_SLEEP_PIN, LOW);
}