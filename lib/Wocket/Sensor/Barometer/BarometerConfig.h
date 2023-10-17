#ifndef WOCKET_BAROMETER_CONFIG_H
#define WOCKET_BAROMETER_CONFIG_H

#include <Wire.h>

struct WocketBarometerConfig {
    int averageReadings;
    TwoWire* wire;
};

#endif // WOCKET_BAROMETER_CONFIG_H
