#include <cstdint>
#include "BuzzerBase.h"

namespace Wocket::Hardware {
    class BuzzerFactory {
    public:
        static BuzzerBase* createBuzzer(uint8_t pin, uint8_t dutyCycle = 0, uint8_t dynamicRange = 0, uint16_t frequency = 0);
    };
}
