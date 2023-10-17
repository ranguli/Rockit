#pragma once

#include <optional>
#include <bitset>

namespace Wocket {
namespace Sensor {

enum class WocketSensorCapability {
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

    virtual std::optional<AccelerationData> getAccelerationReading() const;
    virtual std::optional<float> getPressureReading() const;
    virtual std::optional<float> getTemperatureReading() const;
    virtual std::optional<float> getHumidityReading() const;
    virtual std::optional<float> getAltitudeReading() const;
};

}
}