#pragma once
#include "../setup/modules.h"

// Sets up SD Card on CSPin
void setUpSDCard(){
    // Initialize SD card
    while (!SD.begin(CSPin)) {
        COM_DEBUG.println("SD card initialization failed!");
        delay(1000);
    }
    COM_DEBUG.println("SD card initialized.");
}

// Prints a float data to the file on the SD Card and a comma
void printDataToSDCard(String data) {
    myFile = SD.open(SENSOR_DATA_FILENAME, FILE_WRITE);
    if (myFile) {
        myFile.print(data);
    } else {
        COM_DEBUG.println("Error saving data to file on SD card.");
    }
    myFile.close();
}

void printDataOnSDCard(){
    myFile = SD.open(SENSOR_DATA_FILENAME);
    if (myFile)
    {
        while (myFile.available()) {COM_DEBUG.write(myFile.read());}
        myFile.close();
    } else 
    { 
        // if the file didn't open, print an error:
        COM_DEBUG.println("error opening file to read");
    }
}