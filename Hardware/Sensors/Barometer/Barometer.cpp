#include "Barometer.h"
#include "../../../Config.h"

float Barometer::getAveragePressureReading() {
  float avgPressure = 0.0;

  //Take 16 readings and average them
  for (int i = 0; i < 16; i++) {
    pressure += this->getPressureReading();
  }

  return avgPressure /= (float)16;
}

float Barometer::getAltitudeDelta() {
  // A fancy and foolish calculation someone smarter than I am created for calculating change in altitude.
  return(ALTITUDE_CONVERSION_FACTOR *(1-pow( this->currentPressure/this->averagePressure , 1/PRESSURE_ALTITUDE_EXPONENT)));
}

float Barometer::getTemperature() {
  return this->temperature; 
}

virtual float Barometer::getTemperatureReading() {
    return 0.0f; 
}

float Barometer::getPressure() {
  return this->pressure; 
}

float Barometer::getPressureReading() {
  return 0.0f;
}


