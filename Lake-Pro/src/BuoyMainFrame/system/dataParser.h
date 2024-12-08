// Author: Mechatronics Group 3
// Date: 20-12-2024

#pragma once
#include "../setup/modules.h"

/**
 * @brief Calculates the depth from the reference pressure measured vs. 
 * the pressure outside the cannister under water.
 * @returns Depth in metres.
 * 
 */
float calculateAndOutputDepth(float referencePressure, float outsidePressure){
    depth = (outsidePressure-referencePressure)/(WATER_DENSITY*G_ACC);
    depth = depth*100; // Convert to centimeters
    outputDepth(depth, referencePressure);
    return depth;
}

/**
 * @brief Outputs the depth on the Debug monitor.
 * 
 */
void outputDepth(float depth, float referencePressure){
    DEBUG_SERIAL.println("Depth is " + String(depth));
    DEBUG_SERIAL.println("Ref pressure is " + String(referencePressure));
}

/**
 * @brief Splits the data string received over UART from the cannister to the different global variables.
 * @param data a String with each sensor data separated by a semicolon.
 */
void parseDataFromCannister(String data) {
    int startIndex = 0;
    int endIndex = data.indexOf(";", startIndex);

    floatCount = 0;
    int len_data = (int) data.length();
    
    // Splits the data into a float array, as each data is separated with a semicolon when received.
    while (endIndex != -1 && floatCount < MAX_FLOATS) {
        String token = data.substring(startIndex, endIndex); // saves next number as token, seperatered by ";"
        receivedNumbers[floatCount] = token.toFloat();
        startIndex = endIndex + 1;
        floatCount++;
        endIndex = data.indexOf(";", startIndex);
        if (startIndex > len_data) break; // To prevent "out of array bounds"
    }
    
    // After having split the numbers, each is saved to the global variables
    outsidePressure     = receivedNumbers[0];
    outsideTemperature  = receivedNumbers[1];
    co2_SCD             = receivedNumbers[2];
    temperature_SCD     = receivedNumbers[3];
    humidity_SCD        = receivedNumbers[4];
    pressure_HP20       = receivedNumbers[5];
    humidity_DHT        = receivedNumbers[6];
    temperature_DHT     = receivedNumbers[7];
    oxygenLevel         = receivedNumbers[8];
    CH4_sensorVolt      = receivedNumbers[9];
    CH4ppm              = receivedNumbers[10];
    avg_Temperature     = receivedNumbers[11];
    avg_Humidity        = receivedNumbers[12];

    DEBUG_SERIAL.println(F("Parameter                 Value"));
    DEBUG_SERIAL.println(F("--------------------------------"));

    // Print each parameter with its corresponding value
    DEBUG_SERIAL.print(F("Outside Temperature       "));
    DEBUG_SERIAL.println(outsideTemperature, 2);

    DEBUG_SERIAL.print(F("Outside Pressure          "));
    DEBUG_SERIAL.println(outsidePressure, 2);

    DEBUG_SERIAL.print(F("CO2 (SCD)                 "));
    DEBUG_SERIAL.println(co2_SCD, 2);

    DEBUG_SERIAL.print(F("Temperature (SCD)         "));
    DEBUG_SERIAL.println(temperature_SCD, 2);

    DEBUG_SERIAL.print(F("Humidity (SCD)            "));
    DEBUG_SERIAL.println(humidity_SCD, 2);

    DEBUG_SERIAL.print(F("Pressure (HP20)           "));
    DEBUG_SERIAL.println(pressure_HP20, 2);

    DEBUG_SERIAL.print(F("Humidity (DHT)            "));
    DEBUG_SERIAL.println(humidity_DHT, 2);

    DEBUG_SERIAL.print(F("Temperature (DHT)         "));
    DEBUG_SERIAL.println(temperature_DHT, 2);

    DEBUG_SERIAL.print(F("Oxygen Level              "));
    DEBUG_SERIAL.println(oxygenLevel, 2);

    DEBUG_SERIAL.print(F("CH4 Sensor Voltage        "));
    DEBUG_SERIAL.println(CH4_sensorVolt, 2);

    DEBUG_SERIAL.print(F("CH4 ppm                   "));
    DEBUG_SERIAL.println(CH4ppm, 2);

    DEBUG_SERIAL.print(F("Average Temperature       "));
    DEBUG_SERIAL.println(avg_Temperature, 2);

    DEBUG_SERIAL.print(F("Average Humidity          "));
    DEBUG_SERIAL.println(avg_Humidity, 2);

    DEBUG_SERIAL.println(F("--------------------------------"));

    DEBUG_SERIAL.print("In Equilibrium: ");
    DEBUG_SERIAL.println(inEquilibrium ? "Yes" : "No");
}

/**
 * @brief Splits the data receive from cannister into variables and assigns to global variables. 
 * Prints time to SD card and then prints the data to the SD card.
 * 
 */
void parseDataAndSaveToSDCard(String dataString){
    parseDataFromCannister(dataString);
    printTimeToSD();
    printDataToSDCard(dataString);
}

/**
 * @brief Send a command to the cannister and receive back sensor data.
 * @param command a character command.
 * @returns A string of data.
 * 
 */
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

/**
 * @brief Calculates the standard deviation for use in finding the equilibrium point in CH4 measurements.
 * @param values a pointer to a float array of values.
 * @param size the amount of values in the values array.
 * @returns The standard deviation as a float.
 */
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

/**
 * @brief Updates the CH4_SensorvoltHistory and checks for equilibrium in CH4 measurements
 * @param newCH4_Sensorvolt a measurement.
 * 
 */
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