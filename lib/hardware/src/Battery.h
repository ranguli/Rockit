#ifndef ROCKIT_BATTERY_H
#define ROCKIT_BATTERY_H

extern const int BATTERY_PIN;

// A value below this threshold is considered "low battery"
extern const float LOW_BATTERY_VOLTAGE_THRESHOLD;

float getBatteryVoltage();
bool isLowBattery();
void setLowBatteryLED();

#endif // ROCKIT_BATTERY_H