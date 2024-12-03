#pragma once
#include "../setup/modules.h"

/**
 * @brief Converts the measured CH4 sensor volt to a CH4 ppm using a lot of mathematical constants. 
 * These are found from experiments, so the ones below are only for show right now.
 * @returns CH4 as ppm.
 *
 */
float convertCH4SensorToCH4ppm(float CH4_sensorVolt){
      //CH4ppm conversion
    float Pws = 0;
    float Pw = 0;
    float Vo = 0; 
    float Rs_Ro = 0;
    uint16_t Vc = 5000;  
    float g = 8.740 / pow(10,3);
    float p = 129.83 ;
    float a = 3.2938 ;
    float b = -3.755 ;
    float c = 1.5718 / pow(10,6) ;
    float K = -1.4529;
    uint16_t H2Oppm = 0;

    // Define coefficients for RH to H2Oppm
    float A = 6.116441;
    float m = 7.591386;
    float Tn = 240.7263;
    uint16_t Pressure = 1013; //mbar

    Pws = A * pow(10, ((m*avg_Temperature)/(avg_Temperature+Tn)));
    Pw = avg_Humidity * Pws/100;
    H2Oppm = Pw * pow(10,6)/Pressure;
    Vo = g * H2Oppm + p;
    Rs_Ro = ((Vc/CH4_sensorVolt)-1)/((Vc/Vo)-1);
    return a*pow(Rs_Ro,b) + c*(a*pow(Rs_Ro,b))*H2Oppm + K;
}