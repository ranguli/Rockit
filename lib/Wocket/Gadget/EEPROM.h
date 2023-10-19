#pragma once
#include <cstdint>

namespace Wocket {
namespace Hardware {
    
enum EEPROM_ADDRESSES {
    ADDRESS_AUTO_FLIGHT_MODE_DEPLOY_TIME_MS,
    ADDRESS_TIMER_FLIGHT_MODE_DEPLOY_TIME_MS,
    
    ADDRESS_SERVO_1_START_POSITION,
    ADDRESS_SERVO_1_END_POSITION,

    ADDRESS_SERVO_2_START_POSITION,
    ADDRESS_SERVO_2_END_POSITION,
    ADDRESS_SERVO_2_DEPLOY_TIME_MS
};

class EEPROM {
private:          
    const uint16_t size;           

public:
    void getValue(uint8_t address);
    void setValue(uint8_t address);
};

}
}
