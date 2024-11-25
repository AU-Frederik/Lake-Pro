#pragma once
#include "modules.h"

// Sets up the different communication ways
void setupCommunication(){
    Wire.begin();               // I2C 
    COM_DEBUG.begin(COM_DEBUG_BAUDRATE);            // For printing to monitor
    COM_CANNISTER.begin(COM_CANNISTER_BAUDRATE);    // For RX/TX to cannister
    COM_LORA.begin(COM_LORA_BAUDRATE);              // For RX/TX to LoRa module Wio-E5 

    /*
    // Initialize the Wio-E5 LoRa module
    while (!networkJoined){
        LoRaConfigure();
    }
    */
}