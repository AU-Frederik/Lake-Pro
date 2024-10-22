#include "SCD30.h"
#include <HP20x_dev.h>
#include "Arduino.h"
#include "Wire.h" 
#include <KalmanFilter.h>

/* Instance */
KalmanFilter t_filter;    //temperature filter
KalmanFilter p_filter;    //pressure filter


void printSCDResult(float resultSCD[]);
void printHP20Result();

void setup() {
    // Setup I2C
    Wire.begin();
    Serial.begin(9600);

    // Setup sensors
    HP20x.begin();
    scd30.initialize();
}

void loop() {
    
    // Grove SCD30
    // Result has CO2 on first element, Temperature on second and humidity on third
    float resultSCD[3] = {0};
    if (scd30.isAvailable()) {
        // Print CO2 in ppm, Temperature in C and Humidity in %
        printSCDResult(resultSCD);
    }

    // Grove barometer
    if(HP20x.isAvailable()) {
      // Print pressure in hPa
      printHP20Result();
    } 

    
    delay(2000); // Dont change - SCD30 only works at 2 seconds delay
}

void printSCDResult(float resultSCD[]){
  Serial.println("---------------------------");
  scd30.getCarbonDioxideConcentration(resultSCD);
  Serial.print("CO2 Concentration: ");
  Serial.print(resultSCD[0]);
  Serial.print(" ppm");
  Serial.print("\t");
  
  Serial.print("Temperature = ");
  Serial.print(resultSCD[1]);
  Serial.print(" ℃");
  Serial.print("\t");

  Serial.print("Humidity = ");
  Serial.print(resultSCD[2]);
  Serial.println(" %");
  Serial.println(" ");
}

void printHP20Result(){
  long Pressure = HP20x.ReadPressure();
  float p = Pressure/100.0;
  Serial.println("Filtered pressure:");
  Serial.print(p_filter.Filter(p));
  Serial.println("hPa\n");
}