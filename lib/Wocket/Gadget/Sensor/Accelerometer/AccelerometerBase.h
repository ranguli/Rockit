#pragma once

#include <optional>

#include "SensorBase.h"
#include "AccelerometerConfig.h"
#include "AccelerationData.h"

namespace Wocket {
namespace Sensor {

class AccelerometerBase : public SensorBase {
public:
    virtual ~WocketAccelerometer() = default;
    WocketAccelerometer() = default;
    virtual bool begin() = 0;
    float getAccelerationComponent(float acceleration);
    virtual WocketAccelerationData getAcceleration() = 0;

    virtual std::optional<WocketAccelerationData> getAcceleration() const {
      return {};
    }
};

}
}