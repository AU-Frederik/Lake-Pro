// File: BuoyMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

/*
LORA CODES:
M00: Stop measuring and return to top
MXX: Go to XX meters and start measuring. XX = 01-99
B: Check battery status
S: Check solar status
*/

#include "./setup/modules.h"

// Global variables
float CH4_SensorvoltHistory[NUM_VALUES] = {0};  // Buffer for last 10 values
unsigned int currentIndex = 0;                  // To track where to insert the new value
float lastStdDev = 0.0;                         // Last calculated standard deviation
float tolerance = 0.01;                         // Tolerance for checking equilibrium
bool inEquilibrium = false;                     // Flag to check if the system is in equilibrium


void setup() {
    initAllPins();
    turnOnCannister();
    turnOffCableMotor();
    setupCommunication();
    setupBrakeMotor();
    setupPressureSensor();
    setUpSDCard();
}

void loop() {
    float referencePressure = measureRefPressure();
    
    String commandReceivedFromLora = "M10"; // Set manually right now

    // Check the manual buttons, S -> Manual mode, R -> Automatic mode
    measureMotorPins();
    unbrakeCable();             // Unbrakes the cable if it is braked.
    if (manualMode){
        enableManualMode();
    } else {
        reactToCommand(commandReceivedFromLora);
    }
    
    String dataString = sendCommandToCannisterAndReceiveSensorData(commandReceivedFromLora.charAt(0), 5000);

    parseDataFromCannister(dataString);
    printTimeToSD();
    printDataToSDCard(dataString);

    // Calculates the depth and outputs with reference pressure
    depth = calculateDepth(referencePressure, outsidePressure);
    //outputDepth(depth, referencePressure);
}

String sendCommandToCannisterAndReceiveSensorData(char command, unsigned long timeout){
    CANNISTER_SERIAL.println(command);
    unsigned long startTime = millis();
    delay(500);
    bool isSensorData = false;
    String sensorData = "";

    // Runs while something is received, that has more than 20 characters and runs out before set timeout
    while (CANNISTER_SERIAL.available() > 0 && !isSensorData && startTime - millis() < timeout) {
            sensorData = CANNISTER_SERIAL.readStringUntil('\n');
            DEBUG_SERIAL.print("Sensordata: ");
            DEBUG_SERIAL.println(sensorData);
            if (sensorData.length() > 20){
                isSensorData = true;
                DEBUG_SERIAL.println("Received correct data!");
            }
    }

    return sensorData;
}

// Function to calculate standard deviation
/*float calculateStandardDeviation(float* values, unsigned int size) {
    float sum = 0.0;
    float mean = 0.0;
    float stdDev = 0.0;
    
    // Calculate the mean
    for (unsigned int i = 0; i < size; i++) {
        sum += values[i];
    }
    mean = sum / size;
    
    // Calculate the standard deviation
    for (unsigned int i = 0; i < size; i++) {
        stdDev += pow(values[i] - mean, 2);
    }
    stdDev = sqrt(stdDev / size);
    
    return stdDev;
}

// Function to update the CH4_SensorvoltHistory and check equilibrium
void updateCH4SensorVoltHistory(float newCH4_Sensorvolt) {
    // Store the new value in the history buffer
    CH4_SensorvoltHistory[currentIndex] = newCH4_Sensorvolt;
    currentIndex = (currentIndex + 1) % NUM_VALUES;  // Wrap around when reaching the end
    
    // Calculate the new standard deviation
    float currentStdDev = calculateStandardDeviation(CH4_SensorvoltHistory, NUM_VALUES);
    
    // Compare the change in standard deviation
    if (abs(currentStdDev - lastStdDev) < tolerance) {
        inEquilibrium = true;
    } else {
        inEquilibrium = false;
    }

    // Update the last standard deviation
    lastStdDev = currentStdDev;
}*/

// New version of function - let's test it!
void calibratePosition() {
    const int stabilizationDelay = 500;  // Milliseconds to stabilize before rechecking
    const int stableReadings = 3;  // Number of consecutive readings within stopLimit to consider calibrated
    int yawStableCount = 0, pitchStableCount = 0;  // Counters for stable readings

    while (true) {
        readLDRSensors();
        int yawDifference = LDR_WEST_VALUE - LDR_EAST_VALUE;
        int pitchDifference = LDR_NORTH_VALUE - LDR_SOUTH_VALUE;

        // Yaw calibration
        if (abs(yawDifference) > beginLimit) {
            yawStableCount = 0;  // Reset stability counter
            if (yawDifference > 0) {
                DEBUG_SERIAL.println("Turning Yaw CW");
                turnYawCW();
            } else {
                DEBUG_SERIAL.println("Turning Yaw CCW");
                turnYawCCW();
            }
        } else if (abs(yawDifference) < stopLimit) {
            yawStableCount++;
            if (yawStableCount >= stableReadings) {
                DEBUG_SERIAL.println("Turning Yaw off");
                turnYawOff();
            }
        }

        // Pitch calibration
        if (abs(pitchDifference) > beginLimit) {
            pitchStableCount = 0;  // Reset stability counter
            if (pitchDifference > 0) {
                DEBUG_SERIAL.println("Turning Pitch Up");
                turnPitchUp();
            } else {
                DEBUG_SERIAL.println("Turning Pitch Down");
                turnPitchDown();
            }
        } else if (abs(pitchDifference) < stopLimit) {
            pitchStableCount++;
            if (pitchStableCount >= stableReadings) {
                DEBUG_SERIAL.println("Turning Pitch off");
                turnPitchOff();
            }
        }

        // Exit loop if both yaw and pitch are stable for enough consecutive readings
        if (yawStableCount >= stableReadings && pitchStableCount >= stableReadings) {
            DEBUG_SERIAL.println("Calibration Complete");
            break;
        }

        delay(stabilizationDelay);  // Allow time for the system to stabilize before next check
    }
}

