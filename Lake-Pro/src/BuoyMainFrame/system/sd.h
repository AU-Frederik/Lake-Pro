#pragma once
#include "../setup/modules.h"

// Sets up SD Card on CSPin
void setUpSDCard(){
    // Initialize SD card
    if (!SD.begin(CSPin)) {
        DEBUG_SERIAL.println("SD card initialization failed!");
        delay(1000);
    } else {
        DEBUG_SERIAL.println("SD card initialized.");
    }
}

// Prints a float data to the file on the SD Card and a comma
void printDataToSDCard(String data) {
    myFile = SD.open(SENSOR_DATA_FILENAME, FILE_WRITE);
    if (myFile) {
        myFile.print(data);
    } else {
        DEBUG_SERIAL.println("Error saving data to file on SD card.");
    }
    myFile.close();
}

void printDataOnSDCard(){
    myFile = SD.open(SENSOR_DATA_FILENAME);
    if (myFile)
    {
        while (myFile.available()) {DEBUG_SERIAL.write(myFile.read());}
        myFile.close();
    } else 
    { 
        // if the file didn't open, print an error:
        DEBUG_SERIAL.println("error opening file to read");
    }
}