// File: main.cpp
// Author: Mechatronics Group 3 - Frederik Højer
// Date: 2024-10-22

#include <Arduino.h>
#include <SoftwareSerial.h>

#define rxPin     0
#define txPin     1
#define maxFloats 4  // Number of sensor data that we will receive

SoftwareSerial softSerial(rxPin, txPin);
float receivedNumbers[maxFloats]; // Float array to hold all sensor numbers received

void parseData(String data);

void setup() {
    Serial.begin(9600);
    softSerial.begin(9600);
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

    Serial.print("CO2 [ppm]: ");
    Serial.println(receivedNumbers[0]);
    Serial.print("Temperature [C]: ");
    Serial.println(receivedNumbers[1]);
    Serial.print("Humidity [%]: ");
    Serial.println(receivedNumbers[2]);
    Serial.print("Pressure [hPa]: ");
    Serial.println(receivedNumbers[3]);
    Serial.println("------------------------------");
}