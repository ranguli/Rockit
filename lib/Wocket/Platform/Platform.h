#pragma once

#include <cstdint>
#include "BoardPinout.h"
#include "SensorPackage.h"

namespace Wocket::Platform {

constexpr uint8_t UNUSED_PIN = 255;

class Platform {
public:
    Wocket::Platform::BoardPinout pinout;
    Wocket::Sensor::SensorPackage sensors;
};

}