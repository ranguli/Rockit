#pragma once

#include "SensorBase.h"

namespace Wocket::Hardware {

/** 
 * @class HardwarePackage
 * @brief Class representing a suite of multiple hardware components, such as buzzers, LEDS, etc.
 * 
 * Hello!
*/
class HardwarePackage{
    std::vector<std::unique_ptr<HardwareBase>> hardwares;

public:
    /** @param hardware Hei*/
    void addHardware(std::unique_ptr<HardwareBase> hardware);
    //std::optional<HardwareData> HardwarePackage::getReading(SensorCapability capability) const;
};

}