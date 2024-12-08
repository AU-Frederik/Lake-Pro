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
float tolerance = 1.00;                         // Tolerance for checking equilibrium


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

    String dataString = "";
    float referencePressure = measureRefPressure();
    
    String commandReceivedFromLora = "M10"; // Set manually right now

    // Check the manual buttons, S -> Manual mode, R -> Automatic mode
    measureMotorPins();
    if (manualMode){
        //enableManualMode();
    } else {
        reactToCommand(commandReceivedFromLora);
    }
    
    dataString = sendCommandToCannisterAndReceiveSensorData(commandReceivedFromLora.charAt(0));
    
        DEBUG_SERIAL.print(myRTC.getYear(), DEC);
        DEBUG_SERIAL.print("-");
        DEBUG_SERIAL.print(myRTC.getMonth(century), DEC);
        DEBUG_SERIAL.print("-");
        DEBUG_SERIAL.print(myRTC.getDate(), DEC);
        DEBUG_SERIAL.print(" ");
        DEBUG_SERIAL.print(myRTC.getHour(h12Flag, pmFlag), DEC); //24-hr
        DEBUG_SERIAL.print(":");
        DEBUG_SERIAL.print(myRTC.getMinute(), DEC);
        DEBUG_SERIAL.print(": ");
        DEBUG_SERIAL.print(myRTC.getSecond(), DEC);
        DEBUG_SERIAL.println(" ; ");

    if (isSensorData && countDataReceived > 3){
        parseDataFromCannister(dataString);
        printTimeToSD();
        printDataToSDCard(dataString);
        depth = calculateDepth(referencePressure, outsidePressure); // depth in cm
        outputDepth(depth, referencePressure);
        DEBUG_SERIAL.print("Battery level: ");
        DEBUG_SERIAL.print(BatteryLevel());
        DEBUG_SERIAL.println(" %");
    } else if (dataString.length() > 10 && countDataReceived <= 3) {
        DEBUG_SERIAL.println("Waiting for sensor readings to stabilize...");
    }
}

String sendCommandToCannisterAndReceiveSensorData(char command){
    
    CANNISTER_SERIAL.print(command);
    DEBUG_SERIAL.print("Sending command: ");
    DEBUG_SERIAL.println(command);
    delay(1000);
    String sensorData = "";

    // Runs while something is received, that has more than 20 characters and runs out before set timeout
    if (CANNISTER_SERIAL.available() > 0) {
        sensorData = CANNISTER_SERIAL.readStringUntil('\n');
        countDataReceived++;
        isSensorData = true;
    } else {
        isSensorData = false;
    }

    return sensorData;
}

// Function to calculate standard deviation
float calculateStandardDeviation(float* values, unsigned int size) {
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
}