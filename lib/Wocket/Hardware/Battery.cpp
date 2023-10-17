#include <Arduino.h>

#include "../../../Config.h"
#include "LEDs.h"

using namespace Wocket::Hardware;

const int BATTERY_PIN = 29;
const float LOW_BATTERY_VOLTAGE_THRESHOLD = 3.8;

float Battery::getBatteryVoltage() {

  // Take a reading of the battery voltage.
  int reading = analogRead(BATTERY_PIN);

  // A voltage divider appears to be present in the circuit, so our reading is 
  // only half the real value.
  reading *= 2;

  // Our voltage reading will be between 0-4095, because the RP2040 has a 12-bit analog-to-digital converter (ADC),
  // so it can only represent numbers within the range of 2 to the power of 12 minus one (4095, or MAX_ADC_VALUE).
  // We must convert that to an actual voltage. 
  return reading * ADC_REFERENCE_VOLTAGE / MAX_ADC_VALUE;
}

bool Battery::isLowBattery() {
  if (getBatteryVoltage() < LOW_BATTERY_VOLTAGE_THRESHOLD) {
    return true;
  }
  return false;
}

void Battery::setLowBatteryLED() {
  if (this->isLowBattery()) {
    turnOnLowBatteryLED();
  } else {
    turnOffLowBatteryLED();
  }
}