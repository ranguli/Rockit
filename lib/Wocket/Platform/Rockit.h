#pragma once

#include "Platform.h"
#include "Pinout.h"
#include "SensorPackage.h"

#define USE_ADXL343
#define USE_MS5637

class Rockit : public Platform {
public:

    SensorPackage sensors;

    Pinout pinout {
        .SPI_RX = 20,
        .SPI_TX = 19,
        .SPI_SCK = 18,
        .SPI_CS = 17,
        .I2C_SDA = 10,
        .PIEZO_BUZZER = 12
        .BATTERY_PIN = 29;
    }

    const float LOW_BATTERY_VOLTAGE_THRESHOLD = 3.8;
    const uint8_t MAX_ADC_RESOLTUION = 12;
};