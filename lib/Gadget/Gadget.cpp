#include "Gadget.h"

using namespace Wocket;

/**
void GadgetSuite::addGadget(std::unique_ptr<Gadget> gadget) {
    this->gadgets.push_back(std::move(gadget));
}

bool GadgetSuite::hasCapability(GadgetCapability capability) const {
    for (const auto& gadget: gadgets) {
        if (gadget->getCapabilities()[static_cast<size_t>(capability)]) {
            switch (capability) {
                case GadgetCapability::STATUS_LED:
                    return gadget->getPressureReading();
                case GadgetCapability::TEMPERATURE:
                    return gadget->getTemperatureReading();
                case GadgetCapability::HUMIDITY:
                    return gadget->getHumidityReading();
                case GadgetCapability::ALTITUDE:
                    return gadget->getAltitudeReading();
            }
        }
    }

    return false; 
}

void GadgetSuite::blinkAndBeep(int n) { // Blinks the blue LED every 250 ms and makes the buzzer beep

    bool hasLed = this->hasCapability(GadgetCapability::STATUS_LED);
    bool hasPiezoBuzzer = this->hasCapability(GadgetCapability::PIEZO_BUZZER);

    for (int i=0; i<n; i++) {

      if (hasLed)
        this->turnOnStatusLED();

      if (hasPiezoBuzzer)
        this->turnOnPiezoBuzzer();

      delay(250);
      
      if (hasLed)
        this->turnOffStatusLED();

      if (hasPiezoBuzzer)
        this->turnOffPiezoBuzzer();

      delay(250);
    }
}
**/