// File: SolarArrayMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

#include <Arduino.h>

// Motor and H-bridge constants
const int enablePin = 3; //Needs to support PWM channel
const int control_1Pin = 4; 
const int control_2Pin = 5;


//LDR constants
const int LDR_NORTH_PIN = A0;
int LDR_NORTH_VALUE;

const int LDR_SOUTH_PIN = A1;
int LDR_SOUTH_VALUE;

const int LDR_EAST_PIN = A3;
int LDR_EAST_VALUE;

const int LDR_WEST_PIN = A4;
int LDR_WEST_VALUE;

void checkSun();
void formatOutput();

void turnMotorClockWise();
void turnMotorCounterClockWise();
void turnMotorOff();

void setup() {
    Serial.begin(9600);
    Serial.println("Hello from Solar");

    //LDR Pin setup
    pinMode(LDR_NORTH_PIN,INPUT);
    pinMode(LDR_SOUTH_PIN,INPUT);
    pinMode(LDR_EAST_PIN,INPUT);
    pinMode(LDR_WEST_PIN,INPUT);

    //Motor and Hbridge Pin setup
    pinMode(enablePin, OUTPUT); //default 8-bit resolution
    pinMode(control_1Pin, OUTPUT);
    pinMode(control_2Pin, OUTPUT);
}

void loop() {

    checkSun();
    formatOutput();

    //demo start
    turnMotorClockWise();
    delay(1000);
    turnMotorOff();
    delay(1000);
    turnMotorCounterClockWise();
    delay(1000);
    turnMotorOff();
    delay(1000);

    delay(1000);
    
}


// METHODS (Functions?)
void checkSun() {
    LDR_NORTH_VALUE = analogRead(LDR_NORTH_PIN);
    LDR_SOUTH_VALUE = analogRead(LDR_SOUTH_PIN);
    LDR_EAST_VALUE = analogRead(LDR_EAST_PIN);
    LDR_WEST_VALUE = analogRead(LDR_WEST_PIN);
}

void formatOutput() {
    Serial.print("Difference between North and south values are: ");
    Serial.println(LDR_NORTH_VALUE-LDR_SOUTH_VALUE);

    Serial.print("Difference between East and West values are: ");
    Serial.println(LDR_EAST_VALUE-LDR_WEST_VALUE);

    Serial.println("");
}

void turnMotorClockWise() {
    // temporary speed control, should use LDR readings once properly mapped
    digitalWrite(control_1Pin, HIGH);
    digitalWrite(control_2Pin, LOW);

    for (int speed = 0; speed < 255; speed++) {
        analogWrite(enablePin,speed);
        delay(15);
    }
}

void turnMotorCounterClockWise() {
    // temporary speed control, should use LDR readings once properly mapped
    digitalWrite(control_1Pin, LOW);
    digitalWrite(control_2Pin, HIGH);

    for (int speed = 0; speed < 255; speed++) {
        analogWrite(enablePin, speed);
        delay(15);
    }
}

void turnMotorOff() {
    digitalWrite(control_1Pin, LOW);
    digitalWrite(control_2Pin, LOW);

    for (int speed = 255; speed > 0; speed--) {
        analogWrite(enablePin, speed);
        delay(15);
    }
}