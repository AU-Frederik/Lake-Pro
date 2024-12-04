#pragma once
#include "../setup/modules.h"

/**
 * @brief Measures the voltage on the battery.
 * @return Battery voltage.
 */
float BatteryVoltage() {
  int voltageInt = analogRead(PA_SENSOR_BATT);

  float voltageRead = voltageInt * 5.0f / 1024.0f;

  float voltageBattery = voltageRead * 12.0f / 3.0f + BATTERY_VOLTAGE_OFFSET;

  return voltageBattery;
}

/**
 * @brief Converts the calculated battery voltage to a percentage between 0-100%.
 * @return The battery level as an int. 
 */
int BatteryLevel() {
  float batteryVoltage = BatteryVoltage();

  // Check over/under charged
  if (batteryVoltage < BATTERY_VOLTAGE_MIN) return 0;
  if (batteryVoltage > BATTERY_VOLTAGE_MAX) return 100;

  float batteryLevel = BATTERY_SCALE_A * batteryVoltage * batteryVoltage + BATTERY_SCALE_B * batteryVoltage + BATTERY_OFFSET;

  return (int)batteryLevel;
}

