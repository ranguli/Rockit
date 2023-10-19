#pragma once

#include "Platform.h"
#include "Pinout.h"

#define USE_ADXL343
#define USE_MS5637

class Rockit : public Platform {
public:
    Pinout pinout {
        .SPI_RX = 20,
        .SPI_TX = 19,
        .SPI_SCK = 18,
        .SPI_CS = 17,
        .I2C_SDA = 10,
        .PIEZO_BUZZER = 12,
        .BATTERY_PIN = 29,
    }


    const float LOW_BATTERY_VOLTAGE_THRESHOLD = 3.8;
    const uint8_t MAX_ADC_RESOLTUION = 12;
};

// Servo settings
#define SERVO_0_PIN 28
#define SERVO_1_PIN 27
#define SERVO_POWER_SAVING_TIMEOUT_MS 1999
#define SERVO_DELAY_MS 499
#define SERVO_CURRENT_SPIKE_DELAY_MS 99


#define PIEZO_BUZZER_PIN 12
#define PIEZO_BUZZER_DUTY_CYCLE 50
#define PIEZO_BUZZER_FREQUENCY 4000
#define PIEZO_BUZZER_DYNAMIC_RANGE 100
#define PIEZO_BUZZER_ENABLED 1

