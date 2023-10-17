#include "Config.h"
#include "Accelerometer.h"

float Accelerometer::getAccelerationComponent(float acceleration) {
  return (acceleration / GRAVITY_CONSTANT);
}

