#pragma once

#include <cstdint>

namespace Wocket {
namespace Hardware {

class PiezoBuzzer {
private:          
    const uint8_t pin;
      
public:
    void setupPiezoBuzzer();
    void turnOn();
    void turnOff();
};


}
}