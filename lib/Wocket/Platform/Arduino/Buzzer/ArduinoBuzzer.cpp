#include <Arduino.h>
#include "ArduinoBuzzer.h"

namespace Wocket::Hardware {
    ArduinoBuzzer::ArduinoBuzzer(uint8_t pin, uint8_t dutyCycle, uint8_t dynamicRange, uint16_t frequency) 
        : pin(pin), dutyCycle(dutyCycle), dynamicRange(dynamicRange), frequency(frequency) {
        
        pinMode(pin, OUTPUT);
        analogWriteFreq(frequency);
        analogWriteRange(dynamicRange);
    }

    void ArduinoBuzzer::turnOn() {
        analogWrite(this->pin, this->dutyCycle);
    }

    void ArduinoBuzzer::turnOff() {
        analogWrite(this->pin, 0);
    }
}