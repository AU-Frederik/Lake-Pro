#pragma once
#include "../setup/modules.h"


/**
 * @brief Checks if command sent from buoy is 'M'. If not sets all measurements to 0.
 * If 'M' is sent, it measures all sensors.
 *
 */
String measureAll(char command){

    // Initialize default values
    float co2_SCD               = 0.0;
    float temperature_SCD       = 0.0;
    float humidity_SCD          = 0.0;
    float pressure_HP20         = 0.0;
    float humidity_DHT          = 0.0;
    float temperature_DHT       = 0.0;
    float outsidePressure       = 0.0;
    float outsideTemperature    = 0.0;
    float oxygenLevel           = 0.0;
    float CH4_Sensorvolt        = 0.0;
    float CH4ppm                = 0.0;
    avg_Temperature             = 0.0;
    avg_Humidity                = 0.0;

    // If command is not "M" only outside pressure and temperature is measured
    if (command == 'W'){
        float* BAR100_measurements = BAR100_Measure();
        outsidePressure = BAR100_measurements[0];
        outsideTemperature = BAR100_measurements[1];
    }
    if (command == 'M') {
        // SCD30
        float* SCD_measurements     = SCD30_Measure();
        co2_SCD               = SCD_measurements[0];
        temperature_SCD       = SCD_measurements[1];
        humidity_SCD          = SCD_measurements[2];

        // HP20x
        pressure_HP20         = HP20_Measure();

        // DHT22
        float* DHT_measurements     = DHT22_Measure();
        humidity_DHT          = DHT_measurements[0];
        temperature_DHT       = DHT_measurements[1];

        // BAR100
        float* BAR100_measurements  = BAR100_Measure();
        outsidePressure       = BAR100_measurements[0];
        outsideTemperature    = BAR100_measurements[1];
        
        // FD02
        oxygenLevel           = oxygen_Measure();


        // FIGARO
        float* FIGARO_measurements  = FIGARO_Measure(oxygenLevel);
        CH4_Sensorvolt        = FIGARO_measurements[0];
        CH4ppm                = FIGARO_measurements[1];

        // Calculate average inside temperature and humidity
        avg_Temperature   = (temperature_DHT+temperature_SCD)/2;
        avg_Humidity      = (humidity_DHT+humidity_SCD)/2;
    }

    // Build the dataString
    String dataString = "";
    
    if (command == 'M' || command == 'W'){
        dataString += String(outsidePressure, 2) + ";";
        dataString += String(outsideTemperature, 2) + ";";
        dataString += String(co2_SCD, 2) + ";";
        dataString += String(temperature_SCD, 2) + ";";
        dataString += String(humidity_SCD, 2) + ";";
        dataString += String(pressure_HP20, 2) + ";";
        dataString += String(humidity_DHT, 2) + ";";
        dataString += String(temperature_DHT, 2) + ";";
        dataString += String(oxygenLevel, 2) + ";";
        dataString += String(CH4_Sensorvolt, 2) + ";";
        dataString += String(CH4ppm, 2) + ";";
        dataString += String(avg_Temperature, 2) + ";";
        dataString += String(avg_Humidity, 2) + ";";
    } 

    return dataString;
}

/**
 * @brief Measures CO2, temperature and humidity in the cannister using the SCD30 sensor.
 * @returns A pointer to a float array. Returns empty if SCD30 is not ready. 
 * 
 */
float* SCD30_Measure() {
    static float resultSCD[3] = {0.0f, 0.0f, 0.0f};

    if (isSCD30Ready) {
        scd30.getCarbonDioxideConcentration(resultSCD);
    }
    return resultSCD;
}

/**
 * @brief Measures pressure on the HP20 sensor.
 * @returns The measured pressure in hPa. Returns zero if HP20x is not ready. 
 *
 */
float HP20_Measure()
{
    float pressure = 0;

    if(isHP20xReady) {
        long readPressure = HP20x.ReadPressure();
        pressure = p_filter.Filter(readPressure/100.0);
    }

    return pressure;
}


/**
 * @brief Measures humidity and temperature on the DHT22 sensor.
 * @returns A pointer to a float array of two elements with humidity and temperature respectively.
 *
 */
float* DHT22_Measure() 
{
    static float resultDHT[2] = {0.0f, 0.0f};
    resultDHT[0] = dht22.readHumidity();
    resultDHT[1] = dht22.readTemperature();
    return resultDHT;
}

/**
 * @brief Measures the sensor volt from the ADC connected to the Figaro sensor.
 * @param CH4 a float pointer to the global variable.
 * 
 */
float* FIGARO_Measure(float oxygenLevel){
    static float result_FIGARO[2] = {0.0f, 0.0f};

    float CH4_Sensorvolt = 0;
    if (isADSReady && oxygenLevel > 127 && isMethaneSensorPreheated()){
        CH4_Sensorvolt = ads.readADC_SingleEnded(0);
    }

    float CH4ppm = convertCH4SensorToCH4ppm(CH4_Sensorvolt);
    result_FIGARO[0] = CH4_Sensorvolt;
    result_FIGARO[1] = CH4ppm;
    return result_FIGARO;
}


/**
 * @brief Measures the outside pressure and temperature.
 * @returns A pointer to a float array of two elements with outside pressure in hPa
 * and outside temperature in Celcius respectively.
 * 
 */
float* BAR100_Measure() {
    static float resultBAR100[2] = {0.0f, 0.0f};

    if (isBAR100Ready){
        BAR100.read();
        resultBAR100[0] = BAR100.pressure();
        resultBAR100[1] = BAR100.temperature();
    }

    return resultBAR100;
}


/**
 * @brief Measures the oxygen level using FD02 with UART. 
 * For the FD02 to work it needs to receive the command '#MOXY\r'.
 * @returns A float - the oxygen partial pressure in hPa. 
 * 
 */
float oxygen_Measure(){
    const char command[] = "#MOXY\r"; // Command as raw bytes
    float oxygen = 0;
    // Send the command byte by byte for full control
    for (size_t i = 0; i < sizeof(command) - 1; i++) {
        FD02_SERIAL.write(command[i]); // Send byte to Serial
    }

    // Receives response in a string ala "#MOXY 202000 303030 1"
    String response = "";
    while (FD02_SERIAL.available()) {
      char incomingChar = FD02_SERIAL.read();
      response += incomingChar;
    }

    // Parses the string and extracts the first number, as this is oxygen partial pressure
    if (response.length() > 0) {
        if (response.startsWith("#MOXY")) {
            // Extract values
            int space1 = response.indexOf(' ', 6); // Find first space after "#MOXY"
            oxygen = response.substring(space1 + 1, 6).toFloat() * pow(10,-3);
        }
    }
    return oxygen;
}


