#pragma once
#include <cstdint>

namespace Wocket::Hardware {
/** 
 * @struct Pinout
 * @brief Representation of the hardware pinout of a hardware board. 
 * 
 * This provides a common data structure for describing pin configurations 
 * across different microcontroller boards.
*/
struct Pinout {
    /// Recieve (RX) pin for SPI communication 
    const uint8_t SPI_RX;
    /// Transmit (TX) pin for SPI communication 
    const uint8_t SPI_TX;
    /// Serial clock (SCK) pin for SPI communication 
    const uint8_t SPI_SCK;
    /// Chip select (CS) pin for SPI communication 
    const uint8_t SPI_CS;
    /// Pin for connecting to a piezo buzzer
    const uint8_t PIEZO_BUZZER;
    /// Pin for connecting to a battery 
    const uint8_t BATTERY_PIN;

    const uint8_t I2C_SDA;
    const uint8_t I2C_SCL;

    const uint8_t SERVO_1;
    const uint8_t SERVO_2;

    Pinout(int spi_rx, int spi_tx, int spi_sck, int spi_cs, uint8_t i2c_sda, int piezo_buzzer) 
        : SPI_RX(spi_rx), SPI_TX(spi_tx), SPI_SCK(spi_sck), SPI_CS(spi_cs), I2C_SDA(i2c_sda), PIEZO_BUZZER(piezo_buzzer) {}
};

}