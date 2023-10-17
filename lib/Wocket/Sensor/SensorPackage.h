#pragma once

#include "SensorBase.h"

namespace Wocket::Sensor {

class SensorPackage {
    std::vector<std::unique_ptr<SensorBase>> sensors;

public:
    /** 
     * Add a new sensor to the sensor package.
     * @param sensor 
     */
    void addSensor(std::unique_ptr<SensorBase> sensor);

    /** 
     * Queries all sensors in the package that have a given capability,
     * and returns their readings.
     * @param capability 
     * @return Optionally returns data from any capable sensors.
     */
    std::optional<SensorData> getReading(SensorCapability capability) const;
};

}