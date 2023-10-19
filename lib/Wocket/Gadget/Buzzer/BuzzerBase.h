namespace Wocket::Hardware {

class BuzzerBase {
public:
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
private:
    uint8_t pin, dutyCycle, dynamicRange;
    uint16_t frequency;
};

}
