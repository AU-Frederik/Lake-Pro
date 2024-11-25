// File: SolarArrayMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

#include <Arduino.h>

// Motor and H-bridge constants
const int enablePin = 6; //Needs to support PWM channel
const int control_1Pin = 7; 
const int control_2Pin = 8;
const int maxSpeed = 255; //max is 255 (with 8-bit resolution)


//LDR constants
const int LDR_NORTH_PIN = 2;
int LDR_NORTH_VALUE;

const int LDR_SOUTH_PIN = 3;
int LDR_SOUTH_VALUE;

const int LDR_EAST_PIN = 4;
int LDR_EAST_VALUE;

const int LDR_WEST_PIN = 5;
int LDR_WEST_VALUE;

// Rotiny
const int rotinyCCW = A0;
const int rotinyCW = A1;

// Threshholds
const int beginThreshhold = 50;
const int stopThreshhold = 5;


void checkSun();
void formatOutput();
void calibratePosistion();

// DC
void turnMotorClockWise();
void turnMotorCounterClockWise();
void turnMotorOff();

// rotiny
void turnPitchUp();
void turnPitchDown();
void turnPitchOff();

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

    //Rotiny setup
    pinMode(rotinyCCW, OUTPUT);
    pinMode(rotinyCW, OUTPUT);
}

void loop() {


    
    
}


// Functions

void calibratePosistion() {
    checkSun();
    
    bool yawCalibrated = true;
    bool pitchCalibrated = true;

    if (abs(LDR_EAST_VALUE - LDR_WEST_VALUE) > beginThreshhold) {yawCalibrated = false;}
    if (abs(LDR_NORTH_VALUE - LDR_SOUTH_VALUE) > beginThreshhold) {pitchCalibrated = false;}

    if ((yawCalibrated = true)&&(pitchCalibrated = true)){return;}

    while(true) {
        if (yawCalibrated == false) {
            
            if (abs(LDR_EAST_VALUE - LDR_WEST_VALUE) < stopThreshhold) {
                turnMotorOff();
                yawCalibrated = true;
                }
            else if (LDR_EAST_VALUE > LDR_WEST_VALUE) {
                turnMotorClockWise();
            }
        
            else if (LDR_EAST_VALUE < LDR_WEST_VALUE) {
                turnMotorCounterClockWise();
            }
        }

        if (pitchCalibrated == false) {
            if (abs(LDR_NORTH_VALUE - LDR_SOUTH_VALUE) < stopThreshhold) {
                turnPitchOff();
                pitchCalibrated = true;
                }
            else if (LDR_NORTH_VALUE > LDR_SOUTH_VALUE) {
                turnPitchUp();
            }
        
            else if (LDR_NORTH_VALUE < LDR_SOUTH_VALUE) {
                turnPitchDown();
            }
        }
        if ((yawCalibrated = true)&&(pitchCalibrated = true)){break;}
    }

}

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

    for (int speed = 0; speed < maxSpeed; speed++) {
        analogWrite(enablePin,speed);
        delay(15);
    }
}

void turnMotorCounterClockWise() {
    // temporary speed control, should use LDR readings once properly mapped
    digitalWrite(control_1Pin, LOW);
    digitalWrite(control_2Pin, HIGH);

    for (int speed = 0; speed < maxSpeed; speed++) {
        analogWrite(enablePin, speed);
        delay(15);
    }
}

void turnMotorOff() {
    digitalWrite(control_1Pin, LOW);
    digitalWrite(control_2Pin, LOW);

    for (int speed = maxSpeed; speed > 0; speed--) {
        analogWrite(enablePin, speed);
        delay(15);
    }
}