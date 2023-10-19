#include "BarometerBase.h"
#include "../../../Config.h"

using namespace Wocket::Sensor;

std::optional<float> BarometerBase::getAveragePressureReading(int sampleCount) const {
  float avgPressure = 0.0;

  //Take 16 readings and average them
  for (int i = 0; i < 16; i++) {
    pressure += this->getPressureReading();
  }

  return avgPressure /= (float)16;
  /*/
    if(sampleCount <= 0) return {};

    double totalPressure = 0.0;
    int validReadings = 0;

    for (int i = 0; i < sampleCount; i++) {
        auto pressureReading = getPressure();
        if(pressureReading.has_value()) {
            totalPressure += pressureReading.value();
            validReadings++;
        }
    }

    return validReadings > 0 ? totalPressure / validReadings : std::nullopt;
  */
}

WocketCapabilityFlags BarometerBase::getCapabilities() const {
    return WocketCapabilityFlags(WocketSensorCapability::Pressure);
}

std::optional<float> BarometerBase::getPressureReading() const { return {}; }

std::optional<float> BarometerBase::getAltitudeReading() {
  // A fancy and foolish calculation someone smarter than I am created for calculating change in altitude.
  return(ALTITUDE_CONVERSION_FACTOR *(1-pow( this->currentPressure/this->averagePressure , 1/PRESSURE_ALTITUDE_EXPONENT)));
}


}
}