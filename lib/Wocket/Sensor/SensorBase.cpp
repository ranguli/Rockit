#include "Sensor.h"

using namespace Wocket::Sensor;

SensorBase::~SensorBase() {}

std::optional<WocketAccelerationData> SensorBase::getAccelerationReading() const {
    return {};
}

std::optional<float> SensorBase::getPressureReading() const {
    return {};
}

std::optional<float> SensorBase::getTemperatureReading() const {
    return {};
}

std::optional<float> SensorBase::getHumidityReading() const {
    return {};
}

std::optional<float> SensorBase::getAltitudeReading() const {
    return {};
}