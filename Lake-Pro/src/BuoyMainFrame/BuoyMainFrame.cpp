// Author: Mechatronics Group 3
// Date: 20-12-2024

/*
LORA CODES:
M000: Stop measuring and return to top
MXXX: Go to XXX centimeters and start measuring. XXX = 001-999
B: Check battery status
*/

#include "./setup/modules.h"

void setup() {
    initAllPins();              // Sets pinmode on all pins
    turnOnCannister();          // Sets the cannister pin to HIGH to turn on relay
    turnOffCableMotor();        // Makes sure that the Rotiny cable motor is turned off
    setupCommunication();       // Sets up UART and I2C
    setupBrakeMotor();          // Sets speed and acceleration of brake motor and unbrakes.
    setupPressureSensor();      // Sets up the reference pressure sensor Grove Barometer
    setUpSDCard();              // Sets up SD card reader
}

void loop() {

    String dataString = ""; // Resets the data string each iteration
    float referencePressure = measureRefPressure(); // Measures the reference pressure
    
    String commandReceivedFromLora = "M100"; // Set manually right now, as LoRa has not been implemented

    // Check the manual buttons and moves accordingly. Also changes mode automatic/manual when both buttons are pressed.
    checkMotorButtons();

    // If automatic mode react to the command sent over LoRa
    if (automaticMode){
        reactToCommand(commandReceivedFromLora);
    }
    
    // Send command to cannister and receive sensordata in a String
    dataString = sendCommandToCannisterAndReceiveSensorData(commandReceivedFromLora.charAt(0));

    dataString = sendCommandToCannisterAndReceiveSensorData(commandReceivedFromLora.char(0));

    // This logic ensures that the buoy has three measurements when turning on, before it logs and prints it as they are unstable. 
    if (isSensorData && countDataReceived > 3){
        parseDataAndSaveToSDCard(dataString);
        depth = calculateAndOutputDepth(referencePressure, outsidePressure); // depth in cm
    } else if (dataString.length() > 10 && countDataReceived <= 3) {
        DEBUG_SERIAL.println("Waiting for sensor readings to stabilize...");
    }
}