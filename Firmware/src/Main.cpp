// Firmware version 2.1. Release date: 07.08.2022 //This version of the firmware features a real-coded rotary switch.

// In no respect shall DanInvents be accountable for any liabilities, claims, demands, damages or suits resulting from the use of
// the flight controller and/or this software. By using this software, you assume all risks associated with this product and
// its associated features. While the circuitry and software have been tested, they should be considered experimental and handled
// with caution.

// Before uploading this code make sure that you have downloaded the latest ADXL343 (Adafruit) and MS5637 (Sparkfun) libraries.
// You will also need the Circular Buffer library by Roberto Lo Giacco.
// Thanks to Adafruit, Sparkfun and Roberto for the open source libraries and also to Homemade Multibody Dynamics for a guide into how to log data fast.
// Thanks to MartinMcC for showing how to use a rotary encoder with a microcontroller.
// Special thanks to Barun Basnet for the exceptional work on Kalman filters.
// Special thanks to Earle Philhower for providing the support that allows using the Arduino libraries and IDE with the RP2040.

//Firmware improvements of version 2.1 over version 2:

// Fixed a bug that made the piezo buzzer and the blue LED stay on once launch was detected.
// Selecting the position 3 of the rotary switch allows you to test the servo motors. Servo motor 1 moves from its initial to its final position followed by servo 2 3 seconds later.
// By using position 3 to test the servos you avoid creating unnecessary files in your microSD card.
// Wait for 10 seconds to allow the rocketeer to prepare for launch before the flight computer is armed this avoids creating unnecesary files in your microSD card.


// Firmware improvements of version 2 over version 1.2:

// Changed the sign of the longitudinal acceleration. Now positive acceleration is pointing downwards and negative upwards.
// Changed the way that launch is detected. Now the altitude must be greater than 10 m and the acceleration higher than 2 gs for over 100 ms.
// Modified the Kalman filter parameters. Now the filtered data closely follows the measured values but featuring lower noise. This guarantees accurate apogee detection.
// Modified the frequency at which the flight computer beeps, now it beeps less frequently before launch.
// Now the flight computer goes silent once launch is detected. After 5 minutes, the flight computer beeps and flashes the altitude.
// For example, 5 beeps/flashes followed by 7 beeps/flashes means 57 meters.
// Now the flight computer can rotate a servo 180 degrees (not yet tested).

#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Servo.h>
#include <EEPROM.h>

#include "globals.h"

#include "SparkFun_MS5637_Arduino_Library.h"
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL343.h>

#include "beepnblink.h"
#include "recovery.h"
#include "kalmanFilter.h"
#include "batteryStatus.h"
#include "rotSwitch.h"
#include "preLaunch.h"
#include "SDstartup.h"

CircularBuffer <long,100> times;
CircularBuffer <float,100> FilteredAltitudes;
CircularBuffer <float,100> altitudes;
CircularBuffer <float,100> accelerations;

Servo servo1; //Creates a servo1 object
Servo servo2; //Creates a servo2 object

File dataFile; //Creates a dataFile object
MS5637 barometricSensor; //Creates a barometricSensor object

/* Assign a unique ID to this sensor at the same time */
Adafruit_ADXL343 accelerometer = Adafruit_ADXL343(12345, &Wire1);

void setup() {
  //Serial.begin(9600); //For debugging purposes only
  EEPROM.begin(512); //Emulates EEPROM by allocating 512 kB from the flash memory

  //Declaration of the I2C pins
  Wire1.setSDA(10);
  Wire1.setSCL(11);

  //Declaration of the SPI pins
  SPI.setRX(20);
  SPI.setTX(19);
  SPI.setSCK(18);
  SPI.setCS(17);

  //Declaration of the pins for the battery indicator, and status LED as well as the pin for the buzzer
  pinMode(batLED, OUTPUT); //Low battery LED
  pinMode(statusLED, OUTPUT); //Status LED
  pinMode(piezo, OUTPUT); //Piezo buzzer

  //Piezo buzzer PWM settings
  analogWriteFreq(4000); //Set the piezo frequency to 4kHz
  analogWriteRange(100); //Set the dynamic range of the piezo
   
  for (int i = 0; i < 4; i = i + 1){
     pinMode(switchPins[i], INPUT_PULLUP);
  }

  barometricSensor.begin(Wire1);
  barometricSensor.setResolution(ms5637_resolution_osr_1024);
  
  //Take 16 readings and average them
  startingPressure = 0.0;
  for (int x = 0 ; x < 16 ; x++)
    startingPressure += barometricSensor.getPressure();
  startingPressure /= (float)16;

  accelerometer.begin();
  accelerometer.setRange(ADXL343_RANGE_16_G);
  accelerometer.setDataRate(ADXL343_DATARATE_400_HZ);
  switchStartup(servo1, servo2);
  delay(10000); //Wait for 10 seconds to allow the rocketeer to prepare for launch before the flight computer is armed.
  //preLaunch(barometricSensor, accelerometer, times); //Here I store the first second of data into the circular buffers
  preLaunch(barometricSensor, accelerometer, times, altitudes, accelerations, FilteredAltitudes);

  dataFile = SDstartup();
}

void loop() {
  batteryStatus(); //Check the battery level
  static int q = 0;
  
  if (overtime == false){
    currentPressure = barometricSensor.getPressure();
    temp = barometricSensor.getTemperature();
    sensors_event_t event;
    accelerometer.getEvent(&event);
    rocketAccel = -((event.acceleration.y/9.81)-(event.acceleration.x/9.81))/sqrt(2);
    altitudeDelta = barometricSensor.altitudeChange(currentPressure, startingPressure);
    filteredAltitudeDelta = kalmanFilter(altitudeDelta);
    

    if (altitudeDelta > altThreshold && launchCondition1 == false){ //Threshold condition set to 10 m
      launchCondition1 = true;
    }
    
    if (rocketAccel > accelThreshold && launchCondition2 == false){
      q++;
      if (q > 10){ //launcCondition2 stablishes the requirement that to detect launch there should be at least an acceleration of 2g for 100 ms
        launchCondition2 = true;
      }
    }

    else if (rocketAccel < accelThreshold && launchCondition2 == false){
      q = 0;
    }

    if (initVar == true){ //Store data to the circular buffer
      accelerations.push(rocketAccel);
      altitudes.push(altitudeDelta);
      FilteredAltitudes.push(filteredAltitudeDelta);
      times.push(millis()-t4); //Circular buffer for time

      if (launchCondition1 == true && launchCondition2 == true){
        initVar = false;
          
        for (int i = 0; i<=99; i++){ //Saving the buffer allows me to store the data measured before launch.
         dataFile.print(times[i]-times[0]); //Here times[0] sets the time zero for the time variable
         dataFile.print(',');
         dataFile.print(altitudes.shift());
         dataFile.print(',');
         dataFile.print(FilteredAltitudes.shift());
         dataFile.print(',');
         dataFile.print(accelerations.shift());
         dataFile.print(',');
         dataFile.print(event.acceleration.z/9.81);
         dataFile.print(',');
         dataFile.println(temp, 1);
        }
          
         dataFile.flush(); //Store data of the 908 ms before launch
       }
     }      

    else if (initVar == false){
      t1 = millis() - t4 - times[0];
      recovery(servo1, servo2);  
      dataFile.print(t1);
      dataFile.print(',');
      dataFile.print(altitudeDelta);
      dataFile.print(',');
      dataFile.print(filteredAltitudeDelta);
      dataFile.print(',');
      dataFile.print(rocketAccel);
      dataFile.print(',');
      dataFile.print(event.acceleration.z/9.81);
      dataFile.print(',');
      dataFile.println(temp, 1);

      if (altitudeDelta > altOld){ //Here is where I store the maximum altitude value
        altMax = round(altitudeDelta);
        altOld = altMax;
      }
  
      if (r == 200 && overtime == false){ //Here I set the rate at which I send data to the uSD card
        r = 0;
        dataFile.flush();
       }
       r++;
       
    
      if (t1 >= tout){
        overtime = true;
        dataFile.flush();
        dataFile.close(); //After timeout flush the data to the microSD card and close the file
      }
    }
 }
 beepnblink();
}
