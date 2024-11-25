#pragma once
#include "../setup/modules.h"

/**
 * @brief Sends a command to the Wio-E5 and checks for response "OK"
 * 
 * @param command Format string for the command.
 * @param expectedResponse Expected response, defaults to "OK"
 * @param timeout Response is received for this time, defaults to 2000
 * @return bool true if response "OK" is received, false otherwise.
 */
bool sendCommandAndReceiveResponse(const String &command, const char *expectedResponse, unsigned long timeout){
  COM_LORA.println(command);  // Send command to Wio-E5
  COM_DEBUG.println(command);  // Debugging command
  
  unsigned long startTime = millis();
  // Checks for response before set time out
  while (millis() - startTime < timeout) {
    if (COM_LORA.available()) {
      String response = COM_LORA.readString();
      COM_DEBUG.println(response);

      // If expected response is part of the response received back it returns true
      if (response.indexOf(expectedResponse) >= 0) {
        return true;  // Expected response received
      }
    }
  }
  return false;  // Timeout or response not received
}

/**
 * @brief Initializes the E5 module and configures settings.
 */
bool LoRaConfigure() {
  // LWOTAA (Over the Air Activation), LWABP (Activation By Personalization)
  if (!sendCommandAndReceiveResponse("+MODE: LWOTAA", "AT+MODE=LWOTAA\r\n"), 1000) return false;

  // EU Band
  if (!sendCommandAndReceiveResponse("+DR: EU868", "AT+DR=EU868\r\n", 1000)) return false;

  // Channels
  if (!sendCommandAndReceiveResponse("+CH: NUM", "AT+CH=NUM,0-2\r\n")) return false;

  // Application Session Key
  if (!sendCommandAndReceiveResponse("+KEY: APPKEY", "AT+KEY=APPKEY,\"2B7B151628AED2A6AAF7157609CF4F2C\"\r\n", 1000)) return false;

  // LoRaWAN Class
  if (!sendCommandAndReceiveResponse("+CLASS: A", "AT+CLASS=A\r\n", 1000)) return false;

  // Broadcast Port
  if (!sendCommandAndReceiveResponse("+PORT: 8", "AT+PORT=8\r\n", 1000)) return false;

  return true;
}