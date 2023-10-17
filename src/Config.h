#ifndef WOCKET_CONFIG_H
#define WOCKET_CONFIG_H

#include <cstdint>

#include <Wire.h>

//#include "BarometerConfig.h"

// -------------------
// | Simulation mode |
// -------------------
// Enable simulation mode by setting USE_SIMULATION_MODE to 1.
#define USE_SIMULATION_MODE 0

// ---------------------------------
// | Sensor-Specific Configuration |
// ---------------------------------

// Assign a unique ID to the accelerometer sensor.
const uint8_t ACCELEROMETER_UID = 1;

// The number of pressure readings that should be taken (and then averaged out) to determine the initial barometric pressure on the ground.
const uint8_t BAROMETRIC_INITIAL_AVERAGE_READINGS = 16;

// Uncomment this option if you are using an Adafruit ADXL343 accelerometer.
// You can leave this as is if you're using a standard Rockit.
//#define USE_ADXL343

// Uncomment this option if you are using a Sparkfun MS5637 barometric pressure sensor.
// You can leave this as is if you're using a standard Rockit.
//#define USE_MS5637

// --------------------------------
// | Board-Specific Configuration |
// --------------------------------

// The maximum resolution of the boards analog-to-digital converter (ADC),
// in bits. In the case of an RP2040-based board like the Rockit, 
// which has a 12-bit ADC, the value will be 12. 
// On other micro-controllers, it may be another value. 
extern const uint8_t MAX_ADC_RESOLUTION;

// The reference voltage of the boards ADC. On a Rockit, this is 3.3 volts.
extern const float ADC_REFERENCE_VOLTAGE;

// Pinouts:

// I2C
#define PIN_I2C_SCL 11

// Servo settings
#define SERVO_0_PIN 28
#define SERVO_1_PIN 27
#define SERVO_POWER_SAVING_TIMEOUT_MS 1999
#define SERVO_DELAY_MS 499
#define SERVO_CURRENT_SPIKE_DELAY_MS 99

// SPI
#define PIN_SPI_RX 20
#define PIN_SPI_TX 19
#define PIN_SPI_SCK 18
#define PIN_SPI_CS 17

#define PIEZO_BUZZER_PIN 12
#define PIEZO_BUZZER_DUTY_CYCLE 50
#define PIEZO_BUZZER_FREQUENCY 4000
#define PIEZO_BUZZER_DYNAMIC_RANGE 100
#define PIEZO_BUZZER_ENABLED 1


// --------------------
// | Launch detection |
// --------------------

// Altitude threshold for launch detection. An altitude above the threshold (in meters) means we have launched.
constexpr float LAUNCH_ALTITUDE_THRESHOLD = 10.0;
constexpr float LAUNCH_ACCELERATION_THRESHOLD = 2.0;

// -----------------------
// | Physical magnitudes |
// -----------------------

// Change this for more precision, or if you will be using Wocket on a different planet.
constexpr float GRAVITY_CONSTANT = 9.81;

// This is an empirical constant that helps relate pressure to altitude in meters.
constexpr float ALTITUDE_CONVERSION_FACTOR = 44330.0;

// Mathematical constant use for calculations with the barometric sensor
constexpr float PRESSURE_ALTITUDE_EXPONENT = 5.255;

// ---------------------------------
// | Flight Computer Configuration |
// ---------------------------------

// How many milliseconds the flight computer should wait after being powered on 
// before it should be "armed". The default is 10 seconds.
constexpr unsigned int FLIGHT_COMPUTER_ARM_DELAY_MS = 10000;

// By default, Rockit allows 5 minutes (or 300,000 milliseconds) of data logging time.
constexpr unsigned int FLIGHT_COMPUTER_TIMEOUT_MS = 30000;


// A value below this threshold is considered "low battery"
extern const float LOW_BATTERY_VOLTAGE_THRESHOLD;


// --------------------
// | EEPROM addresses |
// --------------------

enum EEPROM_ADDRESSES {
  ADDRESS_AUTO_FLIGHT_MODE_DEPLOY_TIME_MS,
  ADDRESS_TIMER_FLIGHT_MODE_DEPLOY_TIME_MS,
  
  ADDRESS_SERVO_1_START_POSITION,
  ADDRESS_SERVO_1_END_POSITION,

  ADDRESS_SERVO_2_START_POSITION,
  ADDRESS_SERVO_2_END_POSITION,
  ADDRESS_SERVO_2_DEPLOY_TIME_MS
}; 

Wocket::Sensor::SensorPackage sensorPackage = new Wocket::Sensor::SensorPackage();

#ifdef USE_ADXL343
    #include "ADXL343.h"
    Wocket::Sensor::AccelerometerConfig accelConfig = {123, &Wire1};
    Wocket::Sensor::ADXL343* accelerometer = new Wocket::Sensor::ADXL343(accelConfig);
    sensorPackage.addSensor(std::make_unique<Wocket::Sensor::ADXL343>());
#endif

#ifdef USE_MS5637
    #include "WocketMS5637.h"
    WocketBarometer* barometer = new WocketMS5637();
    WocketBarometerConfig barometerConfig = {BAROMETRIC_INITIAL_AVERAGE_READINGS, &Wire1};
#endif

#endif // WOCKET_CONFIG_H

