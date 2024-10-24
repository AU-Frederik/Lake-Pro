#pragma once
#include "../setup/modules.h"

// Sets up SD Card on CSPin
void setUpSDCard(){
    // Initialize SD card
    if (!SD.begin(CSPin)) {
        Serial.println("SD card initialization failed!");
        return;
    }
    Serial.println("SD card initialized.");
}


// Prints a float data to the file on the SD Card and a comma
void printDataToSDCard(float data) {
    myFile = SD.open("results.txt", FILE_WRITE);
    if (myFile) {
        myFile.print(data);
        myFile.print(",");
        myFile.close();
    } else {
        Serial.println("Error saving data to file on SD card.");
    }
}