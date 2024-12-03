#pragma once
#include "modules.h"

// Sets up the different communication ways
void setupCommunication(){
    Wire.begin();                                   // I2C 
    DEBUG_SERIAL.begin(DEBUG_SERIAL_BAUDRATE);            // For printing to monitor
    CANNISTER_SERIAL.begin(CANNISTER_SERIAL_BAUDRATE);    // For RX/TX to cannister
    COM_LORA.begin(COM_LORA_BAUDRATE);              // For RX/TX to LoRa module Wio-E5 

    /*
    // Initialize the Wio-E5 LoRa module
    while (!networkJoined){
        LoRaConfigure();
    }
    */
}