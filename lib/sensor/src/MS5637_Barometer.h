#ifndef ROCKIT_BAROMETRIC_SENSOR_H
#define ROCKIT_BAROMETRIC_SENSOR_H

#include <Wire.h>
#include "SparkFun_MS5637_Arduino_Library.h"

#include "Barometer.h"

class MS5637_Barometer : public Barometer {
private:
    int uid;                  
    MS5637 sensor;
public:
    using Barometer::Barometer;

    MS5637_Barometer(const BarometerConfig& config);
    bool begin() override;
    float getAveragePressureReading();

    float getTemperature();
    float getTemperatureReading() override;

    float getPressure();
    float getPressureReading() override;
    
    float getAltitudeDelta();
    float getFilteredAltitudeDelta();

};

#endif // ROCKIT_BAROMETRIC_SENSOR_H
