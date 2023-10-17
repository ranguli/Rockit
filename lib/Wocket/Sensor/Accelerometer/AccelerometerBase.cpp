#include "Config.h"
#include "AccelerometerBase.h"

using namespace Wocket::Sensor;

float AccelerometerBase::getAccelerationComponent(float acceleration) {
  return (acceleration / GRAVITY_CONSTANT);
}

