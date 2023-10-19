#pragma once

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>

#include "../Accelerometer.h"
#include "../AccelerometerConfig.h"

namespace Wocket {
namespace Sensor {

class ADXL343: public AccelerometerBase {
private:
    Adafruit_ADXL343 sensor;
public:
    ADXL343(const AccelerometerConfig& config);
    AccelerationData getAcceleration() override;
    bool begin() override;
};

}
}