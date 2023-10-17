#include "SparkFun_MS5637_Arduino_Library.h"
#include "BarometerBase.h"
#include "KalmanFilter.h"

using namespace Wocket::Sensor;

MS5637::MS5637(const BarometerConfig& config) 
: sensor(), avgReadings(config.avgReadings) {}

bool MS5637::begin() {
    if(!this->sensor.begin(config.wire)) {
        return false;
    }

    this->sensor.setResolution(ms5637_resolution_osr_1024);

    this->startingPressure = getAveragePressure(sensor, config.avgReadings);

    return true;
}

float MS5637::getPressureReading() override {
  this->pressure = this->sensor.getPressure();
  return this->pressure;
}

float MS5637::getTemperatureReading() override {
  this->temperature = this->sensor.getTemperature();
  return this->temperature;
}

float MS5637::getAltitudeDelta() {
  return this->sensor.altitudeChange(this->pressure, this->startingPressure) + 0.6; // I don't know the meaning behind the 0.6 :( 
}

float MS5637::getFilteredAltitudeDelta() {
  return(kalmanFilter(this->getAltitudeDelta()));
}
