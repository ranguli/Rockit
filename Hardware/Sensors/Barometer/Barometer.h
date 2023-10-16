#ifndef WOCKET_BAROMETER_H
#define WOCKET_BAROMETER_H

#include "../Sensor.h"

class Barometer : public Sensor {
private:
  float pressure;
public:
  virtual ~Barometer() = default;
  Barometer() = default;
  virtual bool begin() = 0;
  virtual float getPressureReading();
  virtual float getPressure();
  virtual float getTemperatureReading();
  float getAltitudeDelta();
  float getFilteredAltitudeDelta();
  float getAveragePressureReading();
};

#endif // WOCKET_BAROMETER_H