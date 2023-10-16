#ifndef WOCKET_ACCELEROMETER_H
#define WOCKET_ACCELEROMETER_H

#include "AccelerometerConfig.h"
#include "../../SensorData/AccelerationData.h"

class Accelerometer {
public:
    virtual ~Accelerometer() = default;
    Accelerometer() = default;
    virtual bool begin() = 0;
    float getAccelerationComponent(float acceleration);
    virtual AccelerationData getAcceleration() = 0;
};

#endif // WOCKET_ACCELEROMETER_H
