#pragma once
#include "../setup/modules.h"


/**
 * @brief Checks if command sent from buoy is 'M'. If not sets all measurements to 0.
 * If 'M' is sent, it measures all sensors.
 *
 */
void measureAll(){  
    // If message is not M it will only send outsidePressure and depth
    if (command.charAt(0) != 'M'){
        outsidePressure_Measure(&outsidePressure, &outsideTemperature);
        co2_SCD             = 0;
        avg_Humidity        = 0;
        avg_Temperature     = 0;
        pressure_HP20       = 0;
        CH4_sensorVolt      = 0;
        CH4ppm              = 0;
        return;
    }

    // Measure CO2 in ppm, Temperature in C and Humidity in %
    SCD30_Measure(&co2_SCD, &temperature_SCD, &humidity_SCD);

    // Check if barometer is ready, if yes measure pressure in hPa
    HP20_Measure(&pressure_HP20);

    // Measure temperature and humidity
    DHT22_Measure(&humidity_DHT, &temperature_DHT);

    // Measure pressure outside
    outsidePressure_Measure(&outsidePressure, &outsideTemperature);

    calculateAverageTempAndHumidity(&avg_Temperature, &avg_Humidity);

    // Measure oxygen using FD02
    oxygen_Measure(&oxygenLevel);
    
    // Measure CH4 if over 127 hPa as this is 16% oxygen, which is needed for combustion
    if (oxygenLevel > 127 && isMethaneSensorPreheated()) { 
        CH4_Measure(&CH4_sensorVolt);
        convertCH4SensorToCH4ppm(&CH4ppm);
    } else {
        CH4_sensorVolt = 0;
        CH4ppm = 0;
    }
}

/**
 * @brief Measures CO2, temperature and humidity in the cannister using the SCD30 sensor.
 * @param co2 a float pointer to the global variable.
 * @param temperature a float pointer to the global variable.
 * @param humidity a float pointer to the global variable.
 */
void SCD30_Measure(float* co2, float* temperature, float* humidity)
{
    int resultLen = 3;
    // Result has CO2 on first element, Temperature on second and humidity on third
    float resultSCD[resultLen] = {0};

    if (scd30.isAvailable()) {
        scd30.getCarbonDioxideConcentration(resultSCD);
        *co2         = resultSCD[0];
        *temperature = resultSCD[1];
        *humidity    = resultSCD[2];
    }
}

/**
 * @brief Measures pressure on the HP20 sensor.
 * @param pressure a float pointer to the global variable.
 *
 */
void HP20_Measure(float* pressure)
{
    if(HP20x.isAvailable()) {
        long readPressure = HP20x.ReadPressure();
        *pressure = p_filter.Filter(readPressure/100.0);
    } else {
        *pressure = 0;
    }
}


/**
 * @brief Measures humidity and temperature on the DHT22 sensor.
 * @param humidity - a float pointer to the global variable.
 * @param temperature a float pointer to the global variable.
 *
 */
void DHT22_Measure(float* humidity, float* temperature) 
{
    float h   = dht.readHumidity();
    float t   = dht.readTemperature();

    *humidity = isnan(h) ? 0.0 : h;  // fallback to 0.0 if NaN
    *temperature = isnan(t) ? 0.0 : t;  // fallback to 0.0 if NaN
}


/**
 * @brief Measures outside temperature on the TSYS01 sensor.
 * @param temperature a float pointer to the global variable.
 * 
 */
void outsideTemp_Measure(float* temperature)
{
    outsideTempSensor.read();
    float t = outsideTempSensor.temperature();
    *temperature = isnan(t) ? 0.0 : t;  // fallback to 0.0 if NaN
}


/**
 * @brief Measures the sensor volt from the ADC connected to the Figaro sensor.
 * @param CH4 a float pointer to the global variable.
 * 
 */
void CH4_Measure(float* CH4){
    CH4_sensorVolt = ads.readADC_SingleEnded(0);
}


/**
 * @brief Measures the outside pressure.
 * @param pressure a float pointer to the global variable.
 * 
 */
void outsidePressure_Measure(float* pressure, float* temperature) {
    outsidePressureSensor.read();
    *pressure = outsidePressureSensor.pressure();
    *temperature = outsidePressureSensor.temperature();
}


/**
 * @brief Measures the oxygen level using FD02 with UART. 
 * For the FD02 to work it needs to receive the command '#MOXY\r'.
 * @param oxygen a float pointer to the global variable.
 * 
 */
void oxygen_Measure(float *oxygen){
    const char command[] = "#MOXY\r"; // Command as raw bytes
    // Send the command byte by byte for full control
    for (size_t i = 0; i < sizeof(command) - 1; i++) {
        COM_FD02.write(command[i]); // Send byte to Serial
    }

    // Receives response in a string ala "#MOXY 202000 303030 1"
    String response = "";
    while (COM_FD02.available()) {
      char incomingChar = COM_FD02.read();
      response += incomingChar;
    }

    // Parses the string and removes the first number, as this is oxygen partial pressure
    if (response.length() > 0) {
        if (response.startsWith("#MOXY")) {
        // Extract values
        int space1 = response.indexOf(' ', 6); // Find first space after "#MOXY"
        *oxygen = response.substring(space1 + 1, 6).toFloat() * pow(10,-3);
        }
    }
}


