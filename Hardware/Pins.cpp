#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>

#include "Contstants.h"
#include "ServoMotor.h"


void setupPins() {
  setupI2CPins();
  setupSPIPins();
  setupServoPins();
}

void setupServoPins() {
  servo1.setPin(SERVO_1_PIN);
  servo2.setPin(SERVO_2_PIN);
}