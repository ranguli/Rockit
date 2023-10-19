#pragma once

#include <optional>
#include <bitset>

namespace Wocket {
namespace Hardware{

enum class HardwareCapability {
};

using HardwareCapabilityFlags = std::bitset<32>;

/** 
 * @class HardwareBase
 * @brief Base class for a hardware component such as an LED, piezo buzzer, servo motor, etc.
*/

class HardwareBase {
public:
    virtual ~HardwareBase();

    virtual HardwareCapabilityFlags getCapabilities() const = 0;

    virtual std::optional<float> getPressureReading() const;
    virtual std::optional<float> getTemperatureReading() const;
    virtual std::optional<float> getHumidityReading() const;
    virtual std::optional<float> getAltitudeReading() const;
};

}
}
