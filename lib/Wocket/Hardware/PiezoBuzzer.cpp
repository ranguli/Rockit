#include <Arduino.h>
#include "../../Config.h"
#include "PiezoBuzzer.h"

using namespace Wocket::Hardware;

void setupPiezoBuzzer() {
  pinMode(PIEZO_BUZZER_PIN, OUTPUT);

  // Piezo buzzer PWM settings
  analogWriteFreq(PIEZO_BUZZER_FREQUENCY);       // Set the pitch (frequency) the piezo buzzer should beep at.
  analogWriteRange(PIEZO_BUZZER_DYNAMIC_RANGE);  // Set the dynamic range of the piezo buzzer.
}

void turnOnPiezoBuzzer() {
  if (PIEZO_BUZZER_ENABLED == true) {
    analogWrite(PIEZO_BUZZER_PIN, PIEZO_BUZZER_DUTY_CYCLE);
  }
}

void turnOffPiezoBuzzer() {
  if (PIEZO_BUZZER_ENABLED == true) {
    analogWrite(PIEZO_BUZZER_PIN, 0);
  }
}