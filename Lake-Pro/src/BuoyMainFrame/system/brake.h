#pragma once
#include "../setup/modules.h"

void setupBrakeMotor(){
    uint32_t motorSpeed   = 3200; // maximum steps per second (about 3rps / at 16 microsteps)
    uint32_t motorAccel   = 82000; // steps/second/second to accelerate

    stepper.setMaxSpeed(motorSpeed);
    stepper.setAcceleration(motorAccel);
}

// Turns on the brake motor, sets direction to DOWN on the lead screw and moves steps
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

// Turns on the brake motor, sets direction to UP on the lead screw and moves steps
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

void turnOnBrakeMotor(){
    digitalWrite(MOTOR_SLEEP_PIN, HIGH);
}

void shutOffBrakeMotor(){
    digitalWrite(MOTOR_SLEEP_PIN, LOW);
}