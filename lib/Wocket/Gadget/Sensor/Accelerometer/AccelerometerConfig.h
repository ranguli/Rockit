#pragma once

#include <Wire.h>

namespace Wocket {
namespace Sensor {

struct AccelerometerConfig {
    int uid;
    TwoWire* wire;
};

}
}
