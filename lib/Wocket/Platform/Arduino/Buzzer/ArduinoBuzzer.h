#include "BuzzerBase.h"
#include <Arduino.h>

namespace Wocket::Platform::Arduino {
    class ArduinoBuzzer: public BuzzerBase {
    public:
        ArduinoBuzzer(uint8_t pin, uint8_t dutyCycle, uint8_t dynamicRange, uint16_t frequency);
        virtual void turnOn() override;
        virtual void turnOff() override;

    private:
        uint8_t pin, dutyCycle, dynamicRange;
        uint16_t frequency;
    };
}
