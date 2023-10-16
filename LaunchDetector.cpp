#include "LaunchDetector.h"

bool LaunchDetector::checkAltitudeCondition(float altitudeDelta) {
  if (altitudeDelta > this->altitudeThreshold) {
    return true;
  }

  return false;
}

void LaunchDetector::begin(const unsigned int accelerationThreshold, const unsigned int altitudeThreshold) {
  this->accelerationThreshold = accelerationThreshold;
  this->altitudeThreshold = altitudeThreshold;
}

bool LaunchDetector::checkAccelerationCondition(float acceleration) {
  // If the last 10 readings from the accelerometer have been above the launch acceleration threshold,
  // we consider the condition met.
  static unsigned int readingsAboveThreshold = 0;

  if (acceleration > this->accelerationThreshold) {
    readingsAboveThreshold++;
    if (readingsAboveThreshold > 10) {
      readingsAboveThreshold = 0;
      return true;
    }
  } else {
    readingsAboveThreshold = 0;
  }

  return false;
}

bool LaunchDetector::launchDetected(const float acceleration, const float altitudeDelta) {
  if (launched) {
    return true;
  }

  bool accelerationCondition = this->checkAccelerationCondition(acceleration);
  bool altitudeCondition = this->checkAltitudeCondition(altitudeDelta);

  if (accelerationCondition && altitudeCondition) {
    // Houston we have liftoff!
    this->launched = true;
    return true;
  }

  return false;
}