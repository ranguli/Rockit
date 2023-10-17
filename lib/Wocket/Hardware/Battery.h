#pragma once

namespace Wocket {
namespace Hardware {

class Battery {
private:          
    const int pin;           
    const unsigned int id;              
    const float lowBatteryVoltageThreshold;
      
public:
    float getBatteryVoltage();
    bool isLowBattery();
    void setLowBatteryLED();
};

}
}