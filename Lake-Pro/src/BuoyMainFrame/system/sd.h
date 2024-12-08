// Author: Mechatronics Group 3
// Date: 20-12-2024

#pragma once
#include "../setup/modules.h"


/**
 * @brief Sets up the SD card on CSPin
 * 
 */
void setUpSDCard(){
    // Initialize SD card
    if (!SD.begin(CSPin)) {
        DEBUG_SERIAL.println("SD card initialization failed!");
        delay(1000);
    } else {
        DEBUG_SERIAL.println("SD card initialized.");
    }
    
}


/**
 * @brief Print data to the SD card
 * @param data a string of data
 * 
 */
void printDataToSDCard(String data) {
    myFile = SD.open(SENSOR_DATA_FILENAME, FILE_WRITE);
    if (myFile) {
        myFile.print(data);
    } else {
        DEBUG_SERIAL.println("Error saving data to file on SD card.");
    }
    myFile.close();
}