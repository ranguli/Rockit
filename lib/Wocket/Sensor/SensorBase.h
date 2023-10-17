#pragma once

#include <optional>
#include <bitset>

#include "SensorData.h"

namespace Wocket {
namespace Sensor {

enum class SensorCapability {
    CAPABILITY_ACCELERATION = 1 << 0,
    CAPABILITY_PRESSURE = 1 << 1,
    CAPABILITY_TEMPERATURE = 1 << 2,
    CAPABILITY_HUMIDITY = 1 << 3,
    CAPABILITY_ALTITUDE = 1 << 4,
    // ... others ...
};

using WocketCapabilityFlags = std::bitset<32>;

class SensorBase {
public:
    virtual ~SensorBase();

    virtual WocketCapabilityFlags getCapabilities() const = 0;

    virtual std::optional<Wocket::Sensor::SensorData> getAccelerationReading() const;
    virtual std::optional<Wocket::Sensor::SensorData> getPressureReading() const;
    virtual std::optional<Wocket::Sensor::SensorData> getTemperatureReading() const;
    virtual std::optional<Wocket::Sensor::SensorData> getHumidityReading() const;
    virtual std::optional<Wocket::Sensor::SensorData> getAltitudeReading() const;
};

}
}