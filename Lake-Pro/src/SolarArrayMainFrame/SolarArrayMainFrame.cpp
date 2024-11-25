// File: SolarArrayMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

#include "setup/modules.h"

void setup() {
    COM_DEBUG.begin(9600);
    initAllPins();
}

// Each loop the sensors are read and the yaw and pitch motors move towards the sun.
void loop() {
    calibratePosition();
}


/**
 * @brief Follows the sun according to a difference of LDR values using pitch and yaw motors.
 * 
 */
void calibratePosition() {
    readLDRSensors();
    
    bool yawCalibrated   = true;
    bool pitchCalibrated = true;
    int yawDifference    = LDR_WEST_VALUE - LDR_EAST_VALUE;   // Positve if East is biased
    int pitchDifference  = LDR_NORTH_VALUE - LDR_SOUTH_VALUE; // Positive if North is biased

    // Checks if yaw or pitch needs to be calibrated = moved towards the sun
    if (abs(yawDifference)   > beginLimit) {yawCalibrated   = false;}
    if (abs(pitchDifference) > beginLimit) {pitchCalibrated = false;}

    // Do nothing if everything is already calibrated.
    if (yawCalibrated && pitchCalibrated){return;}

    // Each iteration the LDR sensor data is read and the difference is calculated.
    // From this difference a series of actions are done to calibrate.
    // Loop stops when both are calibrated. 
    // The motor will only move when difference is over a threshold.
    while(true) {
        readLDRSensors();
        yawDifference    = LDR_WEST_VALUE - LDR_EAST_VALUE;
        pitchDifference  = LDR_NORTH_VALUE - LDR_SOUTH_VALUE;

        if (abs(yawDifference)   > beginLimit) {yawCalibrated   = false;}
        if (abs(pitchDifference) > beginLimit) {pitchCalibrated = false;}

        if (!yawCalibrated) {
            
            if (abs(yawDifference) < stopLimit) {
                COM_DEBUG.println("Turning Yaw off");
                turnYawOff();
                yawCalibrated = true;
            }

            else if (yawDifference > 0) {
                COM_DEBUG.println("Turning Yaw CW");
                turnYawCW();
            }
        
            else if (yawDifference < 0) {
                COM_DEBUG.println("Turning Yaw CCW");
                turnYawCCW();
            }
        }

        if (!pitchCalibrated) {
            if (abs(pitchDifference) < stopLimit) {
                COM_DEBUG.println("Turning pitch off");
                turnPitchOff();
                pitchCalibrated = true;
            }
            else if (pitchDifference > 0) {
                COM_DEBUG.println("Turning pitch up");
                turnPitchUp();
            }
        
            else if (pitchDifference < 0) {
                COM_DEBUG.println("Turning pitch down");
                turnPitchDown();
            }
        }
        if (yawCalibrated && pitchCalibrated){break;}
    }

}