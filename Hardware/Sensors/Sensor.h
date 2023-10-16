#ifndef WOCKET_SENSOR_H
#define WOCKET_SENSOR_H

class Sensor {
public:
  virtual bool begin();       // Pure virtual function for initialization
};

#endif // WOCKET_SENSOR_H