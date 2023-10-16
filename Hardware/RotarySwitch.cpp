#include <Arduino.h>
#include <EEPROM.h>
#include "pico/stdlib.h"

#include "Pins.h"
#include "State.h"
#include "LEDs.h"
#include "ServoMotor.h"
#include "Constants.h"

static byte previousValue;  //Variable for storing the previous switch possition

// The rotary switch has 16 positions, labelled 0-9 and A-F.
// The position of the rotary switch at boot determines the operating mode
// of the Rockit.

const enum ROTARY_SWITCH {
  ROT_SWITCH_SERVO_2_START_POSITION = 0,
  ROT_SWITCH_SERVO_2_END_POSITION = 1,
  ROT_SWITCH_SERVO_2_DEPLOY_TIME = 2,
  ROT_SWITCH_SERVO_TEST_MODE = 3,

  // Positions 4-9 are unused and will put the Rockit into sleep mode

  ROT_SWITCH_AUTOMATIC_FLIGHT_MODE = 10,          // "A"
  ROT_SWITCH_TIMER_FLIGHT_MODE = 11,              // "B"
  ROT_SWITCH_AUTO_FLIGHT_MODE_DEPLOY_TIME = 12,   // "C"
  ROT_SWITCH_TIMER_FLIGHT_MODE_DEPLOY_TIME = 13,  // "D"
  ROT_SWITCH_SERVO_1_START_POSITION = 14,         // "E"
  ROT_SWITCH_SERVO_1_END_POSITION = 15            // "F"
};


//Config. rotary switch. This configuration is for the real-coded rotary switch

const byte ROTARY_SWITCH_PINS[4] = { 15, 13, 14, 16 };  //Digital pins assigned to the rotary switch

byte rotValue = B0000;  // Variable for printing value over serial debug

// This program reads the rotary switch.

void rotarySwitchSetup() {
  for (int i = 0; i < 4; i = i + 1) {
    pinMode(ROTARY_SWITCH_PINS[i], INPUT_PULLUP);
  }
}

void readRotSwitch() {
  for (int k = 0; k < 4; k++) {
    if (digitalRead(ROTARY_SWITCH_PINS[k]) == LOW) {
      bitSet(rotValue, k);  //sets bit k to 1
    } else {
      bitClear(rotValue, k);  //sets bit k to 0
    }
  }
}

// When the rotary switch has been set to the position marked "A",
// the Rockit is in automatic mode.
void setAutomaticFlightMode() {
  servo1.write(EEPROM.read(ADDRESS_SERVO_1_START_POSITION));
  servo1.attach(PIN_SERVO_1);

  delay(100);  //It is important to have a delay to reduce the current spike drawn by the motors
  servo2.write(EEPROM.read(ADDRESS_SERVO_2_START_POSITION));
  servo2.attach(PIN_SERVO_2);

  automatic = true;
  delay(300);
  blinkStatusLED(EEPROM.read(ADDRESS_AUTO_FLIGHT_MODE_DEPLOY_TIME));
  delay(500);
  blinkStatusLED(EEPROM.read(ADDRESS_SERVO_2_DEPLOYMENT_TIME));
  servo1.detach();  //I detach the servos to save power
  servo2.detach();
  return;
}

void setServoTestMode() {
  servo1.write(EEPROM.read(ADDRESS_SERVO_1_START_POSITION));
  servo1.attach(PIN_SERVO_1);
  delay(500);  //It is important to have a delay to reduce the current spike drawn by the motors
  servo1.detach();

  servo2.write(EEPROM.read(ADDRESS_SERVO_2_START_POSITION));
  servo2.attach(PIN_SERVO_2);
  delay(500);
  servo2.detach();

  blinkStatusLED(2);
  delay(2000);
  servo1.write(EEPROM.read(ADDRESS_SERVO_1_END_POSITION));  //Move servo1 to the final position
  servo1.attach(PIN_SERVO_1);
  blinkStatusLED(2);
  delay(2000);
  servo1.detach();

  servo2.write(EEPROM.read(ADDRESS_SERVO_2_END_POSITION));
  servo2.attach(PIN_SERVO_2);
  delay(500);
  servo2.detach();

  while (1) {
    sleep_ms(100000);
  }
}

void setTimerFlightMode() {
  servo1.write(EEPROM.read(ADDRESS_SERVO_1_START_POSITION));
  servo1.attach(PIN_SERVO_1);

  delay(100);  //It is important to have a delay to reduce the current spike drawn by the motors
  servo2.write(EEPROM.read(ADDRESS_SERVO_2_START_POSITION));
  servo2.attach(PIN_SERVO_2);

  timer = true;
  delay(300);
  blinkStatusLED(EEPROM.read(ADDRESS_TIMER_FLIGHT_MODE_DEPLOY_TIME));
  delay(500);
  blinkStatusLED(EEPROM.read(ADDRESS_SERVO_2_DEPLOYMENT_TIME));
  servo1.detach();  //I detach the servos to save power
  servo2.detach();
  return;
}

ServoMotor getServoFromRotarySwitchPosition(int rotValue) {
  ServoMotor servo;

  switch (rotValue) {
    case ROT_SWITCH_SERVO_1_START_POSITION:
    case ROT_SWITCH_SERVO_1_END_POSITION:
      servo = servo1;
    case ROT_SWITCH_SERVO_2_START_POSITION:
    case ROT_SWITCH_SERVO_2_END_POSITION:
      servo = servo2;
  }

  return servo;
}

int getServoPinFromRotarySwitchPosition(int rotValue) {
  int servoPin;

  switch (rotValue) {
    case ROT_SWITCH_SERVO_1_START_POSITION:
    case ROT_SWITCH_SERVO_1_END_POSITION:
      servoPin = PIN_SERVO_1;
    case ROT_SWITCH_SERVO_2_START_POSITION:
    case ROT_SWITCH_SERVO_2_END_POSITION:
      servoPin = PIN_SERVO_2;
  }

  return servoPin;
}

int getEEPROMAddressFromRotarySwitchPosition(int rotValue) {
  int addressInEEPROM;

  switch (rotValue) {
    case ROT_SWITCH_AUTO_FLIGHT_MODE_DEPLOY_TIME:
      addressInEEPROM = ADDRESS_AUTO_FLIGHT_MODE_DEPLOY_TIME_MS;
      break;
    case ROT_SWITCH_TIMER_FLIGHT_MODE_DEPLOY_TIME:
      addressInEEPROM = ADDRESS_AUTO_FLIGHT_MODE_DEPLOY_TIME_MS;
      break;
    case ROT_SWITCH_SERVO_1_START_POSITION:
      addressInEEPROM = ADDRESS_SERVO_1_START_POSITION;
      break;
    case ROT_SWITCH_SERVO_1_END_POSITION:
      addressInEEPROM = ADDRESS_SERVO_1_END_POSITION;
      break;
    case ROT_SWITCH_SERVO_2_START_POSITION:
      addressInEEPROM = ADDRESS_SERVO_2_START_POSITION;
      break;
    case ROT_SWITCH_SERVO_2_END_POSITION:
      addressInEEPROM = ADDRESS_SERVO_2_END_POSITION;
      break;
    case ROT_SWITCH_SERVO_2_DEPLOY_TIME:
      addressInEEPROM = ADDRESS_SERVO_2_DEPLOYMENT_TIME;
      break;
  }

  return addressInEEPROM;
}

int getDesiredServoPositionFromRotarySwitch(int rotValue) {
  return 180 * rotValue / 15;
}

void deployTimeAdjustmentMode(int rotValue) {
  int addressInEEPROM = getEEPROMAddressFromRotarySwitchPosition(rotValue);

  while (1) {
    readRotSwitch();
    blinkStatusLED(1);
    if (previousValue != rotValue) {
      EEPROM.write(addressInEEPROM, rotValue);
      EEPROM.commit();
      previousValue = rotValue;
    }
  }
}

void servoAdjustmentMode(int rotValue) {
  while (1) {
    readRotSwitch();
    
    int addressInEEPROM = getEEPROMAddressFromRotarySwitchPosition(rotValue);
    int desiredServoPosition = getDesiredServoPositionFromRotarySwitch(rotValue);

    switch (rotValue) {
      case ROT_SWITCH_SERVO_1_START_POSITION:
        servo1.setStartPosition(desiredServoPosition);
        servo1.attach();
        break;
      case ROT_SWITCH_SERVO_1_END_POSITION:
        servo1.setEndPosition(desiredServoPosition);
        servo1.attach();
        break;
      case ROT_SWITCH_SERVO_2_START_POSITION:
        servo2.setStartPosition(desiredServoPosition);
        servo2.attach();
        break;
      case ROT_SWITCH_SERVO_2_END_POSITION:
        servo2.setEndPosition(desiredServoPosition);
        servo2.attach();
        break;
    }

    blinkStatusLED(1);

    if (previousValue != rotValue) {
      EEPROM.write(addressInEEPROM, desiredServoPosition);
      EEPROM.commit();
    }
    previousValue == rotValue;
  }
}

void switchStartup() {
  readRotSwitch();

  switch (rotValue) {
    case ROT_SWITCH_SERVO_1_START_POSITION:
    case ROT_SWITCH_SERVO_1_END_POSITION:
    case ROT_SWITCH_SERVO_2_START_POSITION:
    case ROT_SWITCH_SERVO_2_END_POSITION:
      servoAdjustmentMode(rotValue);
    case ROT_SWITCH_SERVO_2_DEPLOY_TIME:
    case ROT_SWITCH_AUTO_FLIGHT_MODE_DEPLOY_TIME:
    case ROT_SWITCH_TIMER_FLIGHT_MODE_DEPLOY_TIME:
      deployTimeAdjustmentMode(rotValue);
    case ROT_SWITCH_SERVO_TEST_MODE:
      setServoTestMode();
    case ROT_SWITCH_AUTOMATIC_FLIGHT_MODE:
      setAutomaticFlightMode();
      break;
    case ROT_SWITCH_TIMER_FLIGHT_MODE:
      setTimerFlightMode();
      break;
    default:
      while (1);
  }
}