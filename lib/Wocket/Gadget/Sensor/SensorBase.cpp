#include "Sensor.h"

using namespace Wocket::Gadget;

SensorBase::~GadgetBase() {}

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