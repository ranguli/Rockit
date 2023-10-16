#ifndef WOCKET_ADXL343_ACCELEROMETER_H
#define WOCKET_ADXL343_ACCELEROMETER_H

#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>
#include "Accelerometer.h"
#include "AccelerometerConfig.h"

class ADXL343_Accelerometer : public Accelerometer {
private:
    Adafruit_ADXL343 sensor;
public:
    ADXL343_Accelerometer(const AccelerometerConfig& config);
    AccelerationData getAcceleration() override;
    bool begin() override;
};

#endif // WOCKET_ADXL343_ACCELEROMETER_H