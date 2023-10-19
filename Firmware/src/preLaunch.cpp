#include "globals.h"
#include "kalmanFilter.h"
#include "SparkFun_MS5637_Arduino_Library.h"
#include <Adafruit_ADXL343.h>
#include "CircularBuffer.h"

void preLaunch(MS5637 barometricSensor, Adafruit_ADXL343 accelerometer, CircularBuffer<long, 100> &times, CircularBuffer<float, 100> &altitudes, CircularBuffer<float, 100> &accelerations, CircularBuffer<float, 100> &FilteredAltitudes) {
  long t4 = millis();
    
  for (int i = 0; i<=99; i++){
    currentPressure = barometricSensor.getPressure();
    sensors_event_t event;
    accelerometer.getEvent(&event);
    rocketAccel = ((event.acceleration.y/9.81+0.01)-(event.acceleration.x/9.81-0.04))/sqrt(2);
    accelerations.push(rocketAccel);
    altitudeDelta = barometricSensor.altitudeChange(currentPressure, startingPressure)+0.6;
    altitudes.push(altitudeDelta);
    FilteredAltitudes.push(kalmanFilter(altitudeDelta));
    times.push(millis()-t4);
  }  
}