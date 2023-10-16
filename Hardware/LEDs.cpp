#include <Arduino.h>

#include "LEDs.h"
#include "Pins.h"

const int BATTERY_LED_PIN = 2;  // Battery indicator LED
const int STATUS_LED_PIN = 26;  // Status LED, used to indicate errors to the user

void setupLEDs() {
  pinMode(BATTERY_LED_PIN, OUTPUT);  // Low battery LED
  pinMode(STATUS_LED_PIN, OUTPUT);   // Status LED
}

void turnOnStatusLED() {
  // Turn on the blue status LED.
  digitalWrite(STATUS_LED_PIN, HIGH);
}

void turnOffStatusLED() {
  // Turn off the blue status LED .
  digitalWrite(STATUS_LED_PIN, LOW);
}

void blinkStatusLED(int n) {  // Blinks the blue status LED every 200 ms
  for (int i = 0; i <= n; i++) {
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(200);
    digitalWrite(STATUS_LED_PIN, LOW);
    delay(200);
  }
}

void turnOnLowBatteryLED() {
  digitalWrite(BATTERY_LED_PIN, HIGH);
}

void turnOffLowBatteryLED() {
  digitalWrite(BATTERY_LED_PIN, LOW);
}