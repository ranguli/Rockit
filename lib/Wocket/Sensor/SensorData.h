#pragma once

namespace Wocket {
namespace Sensor {

struct Acceleration {
    float x;
    float y;
    float z;
};

struct SensorData {
    Acceleration acceleration;
};

}
}