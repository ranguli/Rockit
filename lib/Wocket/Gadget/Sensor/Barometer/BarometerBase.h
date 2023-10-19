#pragma once

#include "SensorBase.h"

namespace Wocket {
namespace Sensor {

class BarometerBase : public SensorBase {
public:
    WocketCapabilityFlags getCapabilities() const override;

    virtual std::optional<float> getPressureReading() const = 0;
    std::optional<float> getAveragePressureReading(int sampleCount = 16) const;

    std::optional<float> getTemperatureReading() const override;
    std::optional<float> getHumidityReading() const override;
    std::optional<float> getAltitudeReading() const override;
};

}
}