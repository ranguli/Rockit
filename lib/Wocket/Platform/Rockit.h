#pragma once

#include "WocketPlatform.h"
#include "WocketPinout.h"
#include "WocketSensorPackage.h"

#define USE_ADXL343
#define USE_MS5637

class Rockit : public WocketPlatform {
public:

    WocketSensorPackage sensors;

    WocketPinout pinout {
        .SPI_RX = 20,
        .SPI_TX = 19,
        .SPI_SCK = 18,
        .SPI_CS = 17,
        .I2C_SDA = 10,
        .PIEZO_BUZZER = 12
    }
};
