#include <SD.h>
#include <EEPROM.h>
#include "pico/stdlib.h"

#include <Wire.h>
#include <SPI.h>

#include "CircularBuffer.h"

#include "Config.h"
#include "DataLogger.h"
#include "KalmanFilter.h"

#include "Pins.h"
#include "LEDs.h"
#include "Battery.h"
#include "ServoMotor.h"

#include "WocketAccelerationData.h"

//#include "Hardware/Sensors/BarometricSensor.h"

#include "BeepAndBlink.h"

//#include "stages/RecoveryStage.h"
//#include "stages/PreLaunchStage.h"

#include "RotarySwitch.h"
#include "State.h"

#include "LaunchDetector.h"


CircularBuffer<float, 100> FilteredAltitudes;
CircularBuffer<float, 100> altitudes;
CircularBuffer<float, 100> accelerations;
CircularBuffer<long, 100> times;

//Physical magnitudes
float altold;  //Baseline pressure
int altMax;    //Rounded maximum altitude

float temp;
float currentPressure;
float altitudeDelta;
float filteredAltitudeDelta;
float acceleration;

//Definition of time and auxiliary integers
int tconfig, n, p = 0, r = 0;
int deltat;   //Time step of every loop iteration
long int t1;  //Time variables
long int t4;

LaunchDetector launchDetector;

// Create a Logger object, and log file.
DataLogger logger;
File logfile;

void setup() {
  //Serial.begin(9600); //For debugging purposes only
  EEPROM.begin(512);  //Emulates EEPROM by allocating 512 kB from the flash memory

  Wire1.setSDA(PIN_I2C_SDA);
  Wire1.setSCL(PIN_I2C_SCL);


  SPI.setRX(PIN_SPI_RX);
  SPI.setTX(PIN_SPI_TX);
  SPI.setSCK(PIN_SPI_SCK);
  SPI.setCS(PIN_SPI_CS);

  setupLEDs();

  rotarySwitchSetup();

  barometer->begin();
  accelerometer->begin();

  switchStartup();

  delay(FLIGHT_COMPUTER_ARM_DELAY_MS);  //Wait for 10 seconds to allow the rocketeer to prepare for launch before the flight computer is armed.
  //preLaunchStage();                     //Here I store the first second of data into the circular buffers

  launchDetector.begin(LAUNCH_ACCELERATION_THRESHOLD, LAUNCH_ALTITUDE_THRESHOLD);

  logger.begin();
  String logFilename = logger.getNewLogFilename();
  logfile = logger.open(logFilename);
}


void logPreLaunchData() {
  accelerations.push(acceleration);
  altitudes.push(altitudeDelta);
  FilteredAltitudes.push(filteredAltitudeDelta);
  times.push(millis() - t4);  //Circular buffer for time

  for (int i = 0; i <= 99; i++) {        //Saving the buffer allows me to store the data measured before launch.
  /**
    logfile.print(times[i] - times[0]);  //Here times[0] sets the time zero for the time variable
    logfile.print(',');
    logfile.print(altitudes.shift());
    logfile.print(',');
    logfile.print(FilteredAltitudes.shift());
    logfile.print(',');
    logfile.print(accelerations.shift());
    logfile.print(',');
    logfile.print(event.acceleration.z / 9.81);
    logfile.print(',');
    logfile.println(temp, 1);
    **/
  }

  logfile.flush();  //Store data of the 908 ms before launch
}

void flightLoop() {
  /** The rockit can be in one of four different flight states:
   *  - 1) On the ground, pre-launch.
   *  - 2) Post launch, in mid-flight
   *  - 3) Post launch, in recovery
   *  - 4) Post launch,
   **/


  static bool flightIsOver = false;

  if (flightIsOver) {
    // Beep and blink indefinitely, never return.
    beepnblink();
  }

  barometer->getPressureReading();
  temp = barometer->getTemperatureReading();
  WocketAccelerationData accelerationData = accelerometer->getAccelerationReading();

  altitudeDelta = barometer->getAltitudeDelta();
  filteredAltitudeDelta = barometer->getFilteredAltitudeDelta();

  // Store data to the circular buffer
  if (!launchDetector.launchDetected(acceleration, altitudeDelta)) {
    logPreLaunchData();
  }

  t1 = millis() - t4 - times[0];
  
  //recoveryStage();

  /**
  logfile.print(t1);
  logfile.print(',');
  logfile.print(altitudeDelta);
  logfile.print(',');
  logfile.print(filteredAltitudeDelta);
  logfile.print(',');
  logfile.print(acceleration);
  logfile.print(',');
  logfile.print(event.acceleration.z / 9.81);
  logfile.print(',');
  logfile.println(temp, 1);
  **/

  if (altitudeDelta > altold) {  //Here is where I store the maximum altitude value
    altMax = round(altitudeDelta);
    altold = altMax;
  }

  if (r == 200 && flightIsOver == false) {  //Here I set the rate at which I send data to the uSD card
    r = 0;
    logfile.flush();
  }
  r++;


  if (t1 >= FLIGHT_COMPUTER_TIMEOUT_MS) {
    flightIsOver = true;
    logfile.flush();
    logfile.close();  //After timeout flush the data to the microSD card and close the file
  }
}

void loop() {
  // Set the low battery LED if battery voltage is low.
  setLowBatteryLED();

  flightLoop();
}
