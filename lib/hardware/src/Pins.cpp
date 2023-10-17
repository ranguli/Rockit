#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "ServoMotor.h"
#include "Config.h"

void setupPins() {
  setupServoPins();
}

void setupServoPins() {
  servo1.setPin(SERVO_1_PIN);
  servo2.setPin(SERVO_2_PIN);
}