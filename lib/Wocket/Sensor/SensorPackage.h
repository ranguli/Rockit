#pragma once

#include "SensorBase.h"

namespace Wocket {
namespace Sensor {

class SensorPackage {
    std::vector<std::unique_ptr<SensorBase>> sensors;

public:
    // Method to add sensors
    void addSensor(std::unique_ptr<SensorBase> sensor);
    std::optional<SensorData> SensorPackage::getReading(SensorCapability capability) const;
};

}
}