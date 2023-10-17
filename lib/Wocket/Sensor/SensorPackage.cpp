#include "SensorPackage.h"
#include "SensorBase.h"
#include "SensorData.h"

using namespace Wocket::Sensor;

void SensorPackage::addSensor(std::unique_ptr<SensorBase> sensor) {
    sensors.push_back(std::move(sensor));
}

std::optional<SensorData> SensorPackage::getReading(SensorCapability capability) const {
    for (const auto& sensor : sensors) {
        if (sensor->getCapabilities()[static_cast<size_t>(capability)]) {
            switch (capability) {
                case SensorCapability::Pressure:
                    return sensor->getPressureReading();
                case SensorCapability::Temperature:
                    return sensor->getTemperatureReading();
                case SensorCapability::Humidity:
                    return sensor->getHumidityReading();
                case SensorCapability::Altitude:
                    return sensor->getAltitudeReading();
                // ... other capabilities ...
            }
        }
    }
    return {};
}