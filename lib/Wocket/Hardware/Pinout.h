#pragma once

#include <cstdint>

struct Pinout {
    const uint8_t SPI_RX;
    const uint8_t SPI_TX;
    const uint8_t SPI_SCK;
    const uint8_t SPI_CS;
    const uint8_t PIEZO_BUZZER;

    const uint8_t I2C_SDA;

    Pinout(int spi_rx, int spi_tx, int spi_sck, int spi_cs, uint8_t i2c_sda, int piezo_buzzer) 
        : SPI_RX(spi_rx), SPI_TX(spi_tx), SPI_SCK(spi_sck), SPI_CS(spi_cs), I2C_SDA(i2c_sda), PIEZO_BUZZER(piezo_buzzer) {}
};