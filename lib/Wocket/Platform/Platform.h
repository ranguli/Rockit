#pragma once

#include "BoardPinout.h"
#include "SensorPackage.h"

class Platform {
public:
    Wocket::Platform::BoardPinout pinout;
    Wocket::Sensor::SensorPackage sensors;
};
