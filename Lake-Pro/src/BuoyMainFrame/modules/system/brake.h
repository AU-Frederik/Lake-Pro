#pragma once
#include "../setup/modules.h"

void setupBrakeMotor(){
    uint32_t motorSpeed   = 3200; // maximum steps per second (about 3rps / at 16 microsteps)
    uint32_t motorAccel   = 80000; // steps/second/second to accelerate

    stepper.setMaxSpeed(motorSpeed);
    stepper.setSpeed(motorSpeed);
    stepper.setAcceleration(motorAccel);
}

// Turns on the brake motor, sets direction to DOWN on the lead screw and moves steps
void brakeCable(){
    turnOnBrakeMotor();
    setMotorDirection(0);
    stepper.moveTo(stepsToBrake); // 1 rev = 3200
    while (stepper.currentPosition() != stepsToBrake){
        stepper.run();
    }
    stepper.runToNewPosition(0);
    shutOfBrakeMotor();
}

// Turns on the brake motor, sets direction to UP on the lead screw and moves steps
void unbrakeCable(){
    turnOnBrakeMotor();
    setMotorDirection(1);
    stepper.moveTo(stepsToBrake); // 1 rev = 3200
    while (stepper.currentPosition() != stepsToBrake){
        stepper.run();
    }
    stepper.runToNewPosition(0);
    shutOfBrakeMotor();
}

void turnOnBrakeMotor(){
    digitalWrite(MOTOR_SLEEP_PIN, HIGH);
}

void shutOfBrakeMotor(){
    digitalWrite(MOTOR_SLEEP_PIN, LOW);
}

// 1 means moving down on the lead screw or else it moves up
void setMotorDirection(int dir){
    if (dir == 1){
        digitalWrite(MOTOR_DIR_PIN, HIGH);
    } else {
        digitalWrite(MOTOR_DIR_PIN, LOW);
    }
}