// File: BuoyMainFrame.cpp
// Author: Mechatronics Group 3
// Date: 2024-10-22

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <SD.h>

#define rxPin     0
#define txPin     1
#define CSPin     10
#define maxFloats 4  // Number of sensor data that we will receive

// Setup serial to receive data on
SoftwareSerial softSerial(rxPin, txPin);
float receivedNumbers[maxFloats]; // Float array to hold all sensor numbers received

// File on SD Card
File myFile;

// Function declaration
void parseData(String data);

void setup() {
    pinMode(CSPin, OUTPUT);
    Serial.begin(9600);
    softSerial.begin(9600);
    // Initialize SD card
    if (!SD.begin(CSPin)) {
        Serial.println("SD card initialization failed!");
        return;
    }
    Serial.println("SD card initialized.");
}

void loop() {

    if (softSerial.available() > 0) {
        String receivedString = softSerial.readStringUntil('\n');
        parseData(receivedString);
    }
}

void parseData(String data) {
    int startIndex = 0;
    int endIndex = data.indexOf(";", startIndex);
    int floatCount = 0;
    int len_data = (int) data.length();

    while (floatCount < maxFloats) {
        String token = data.substring(startIndex, endIndex); // saves next number as token, seperatered by ";"
        receivedNumbers[floatCount] = token.toFloat();
        startIndex = endIndex + 1;
        floatCount++;
        endIndex = data.indexOf(";", startIndex);
        if (startIndex > len_data) break; // To prevent "out of array bounds"
    }

    myFile = SD.open("test.txt", FILE_WRITE);
    if (myFile) {
        myFile.print("CO2 [ppm]: ");
        myFile.println(receivedNumbers[0]);
        myFile.print("Temperature [C]: ");
        myFile.println(receivedNumbers[1]);
        myFile.print("Humidity [%]: ");
        myFile.println(receivedNumbers[2]);
        myFile.print("Pressure [hPa]: ");
        myFile.println(receivedNumbers[3]);
        myFile.println("------------------------------");
        
        myFile.close();
    } else {
        Serial.println("Error saving data to file on SD card.");
    }
}