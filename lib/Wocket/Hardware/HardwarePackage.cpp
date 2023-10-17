#include "HardwarePackage.h"

using namespace Wocket::Hardware;

void HardwarePackage::addHardware(std::unique_ptr<HardwareBase> hardware) {
    hardwares.push_back(std::move(hardware));
}

bool HardwarePackage::hasCapability(HardwareCapability capability) const {
    for (const auto& hardware: hardwares) {
        if (hardware->getCapabilities()[static_cast<size_t>(capability)]) {
            switch (capability) {
                case HardwareCapability::LED:
                    return sensor->getPressureReading();
                case SensorCapability::Temperature:
                    return sensor->getTemperatureReading();
                case SensorCapability::Humidity:
                    return sensor->getHumidityReading();
                case SensorCapability::Altitude:
                    return sensor->getAltitudeReading();
            }
        }
    }

    return false; 
}

void HardwarePackage::blinkAndBeep(int n) { // Blinks the blue LED every 250 ms and makes the buzzer beep

    bool hasLed = this->hasCapability(CAPABILITY_STATUS_LED);
    bool hasPiezoBuzzer = this->hasCapability(CAPABILITY_PIEZO_BUZZER);

    for (int i=0; i<n; i++) {

      if (hasLed)
        this->turnOnStatusLED();

      if (hasPiezoBuzzer)
        this->turnOnPiezoBuzzer();

      delay(250);
      
      if (hasLed)
        this->turnOffStatusLED();

      if (hasPiezoBuzzer)
        this->turnOffPiezoBuzzer();

      delay(250);
    }
}
