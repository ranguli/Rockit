#ifndef ROCKIT_BAROMETRIC_SENSOR_H
#define ROCKIT_BAROMETRIC_SENSOR_H

#include <Wire.h>
#include "SparkFun_MS5637_Arduino_Library.h"

#include "BarometerBase.h"

class MS5637: public BarometerBase {
private:
    int uid;                  
    MS5637 sensor;
public:
    using Barometer::Barometer;

    WocketMS5637(const WocketBarometerConfig& config);
    bool begin() override;
    float getAveragePressureReading();

    float getTemperature();
    float getTemperatureReading() override;

    float getPressure();
    float getPressureReading() override;
    
    float getAltitudeDelta();
    float getFilteredAltitudeDelta();

#pragma once

#include "WocketBarometer.h"

class WocketMS5637 : public WocketBarometer {
public:
    WocketCapabilityFlags getCapabilities() const override;

    std::optional<double> getTemperatureReading() const override;
    std::optional<double> getPressureReading() const override;
    std::optional<double> getAltitudeReading() const override;
};
