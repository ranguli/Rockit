#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>
#include "ADXL343_Accelerometer.h"

#include "AccelerationData.h"

ADXL343_Accelerometer::ADXL343_Accelerometer(const AccelerometerConfig& config) 
: sensor(config.uid, config.wire) {}

bool ADXL343_Accelerometer::begin() {
  if(!this->sensor.begin()) {
      return false;
  }

  this->sensor.setRange(ADXL343_RANGE_16_G);
  this->sensor.setDataRate(ADXL343_DATARATE_400_HZ);

  return true;
}

AccelerationData ADXL343_Accelerometer::getAcceleration() override {
  sensors_event_t event;
  this->sensor.getEvent(&event);

  AccelerationData data;

  data.x = this->getAccelerationComponent(event.acceleration.x);
  data.y = this->getAccelerationComponent(event.acceleration.y);
  data.z = this->getAccelerationComponent(event.acceleration.z);

  return data;

  // return -(ay - ax) / sqrt(2); // Why sqrt(2)
}