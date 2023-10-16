#ifndef WOCKET_ACCELEROMETER_CONFIG_H
#define WOCKET_ACCELEROMETER_CONFIG_H

#include <Wire.h>

struct AccelerometerConfig {
    int uid;
    TwoWire* wire;
};

#endif
