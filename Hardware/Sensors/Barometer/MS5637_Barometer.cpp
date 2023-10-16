#include "SparkFun_MS5637_Arduino_Library.h"
#include "MS5637_Barometer.h"
#include "../../../Util/KalmanFilter.h"

#include "MS5637_Barometer.h"

MS5637_Barometer::MS5637_Barometer(const BarometerConfig& config) 
: sensor(), avgReadings(config.avgReadings) {}

bool MS5637_Barometer::begin() {
    if(!this->sensor.begin(config.wire)) {
        return false;
    }

    this->sensor.setResolution(ms5637_resolution_osr_1024);

    this.startingPressure = getAveragePressure(sensor, readings);

    return true;
}

float MS5637_Barometer::getPressureReading() override {
  this->pressure = this->sensor.getPressure();
  return this->pressure;
}

float MS5637_Barometer::getTemperatureReading() override {
  this->temperature = this->sensor.getTemperature();
  return this->temperature;
}

float MS5637_Barometer::getAltitudeDelta() {
  return this->sensor.altitudeChange(this->pressure, this->startingPressure) + 0.6; // I don't know the meaning behind the 0.6 :( 
}

float MS5637_Barometer::getFilteredAltitudeDelta() {
  return(kalmanFilter(this->getAltitudeDelta()));
}
