#pragma once

#include "SparkFun_MS5637_Arduino_Library.h"
#include <Adafruit_ADXL343.h>
#include "CircularBuffer.h"

void preLaunch(MS5637 barometricSensor, Adafruit_ADXL343 accelerometer, CircularBuffer<long, 100> &times, CircularBuffer<float, 100> &altitudes, CircularBuffer<float, 100> &accelerations, CircularBuffer<float, 100> &FilteredAltitudes);