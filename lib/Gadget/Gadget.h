#pragma once

namespace Wocket {

    struct Acceleration {
        float x;
        float y;
        float z;
    };

    struct GadgetData {
        Acceleration acceleration;
        float temperature;
        float pressure;
        float humidity;
        float altitude;
    };

    class Gadget {
    protected:
        int capabilities;

    public:
        enum Capability {
            ACCELERATION = 1 << 0,
            PRESSURE = 1 << 1,
            TEMPERATURE = 1 << 2,
            HUMIDITY = 1 << 3,
            ALTITUDE = 1 << 4,
            STATUS_LED = 1 << 5,
            BATTERY_LED = 1 << 6,
            PIEZO_BUZZER = 1 << 7,
            SERVO = 1 << 8,
        };

        void setCapabilities(int caps) {
            this->capabilities = caps;
        };

        //Gadget(int caps) : capabilities(caps) {}
        Gadget() {}
        virtual ~Gadget() {}

        bool hasCapability(Capability cap) const {
            return (this->capabilities & cap) != 0;
        }
    };

    #if 0
    /** A gadget suite represents all gadgets onboard the flight computer. It encompasses LEDs, piezo buzzers, accelerometers, etc. */
    class GadgetSuite {
        std::vector<std::unique_ptr<Gadget>> gadgets;

    public:
        /** 
         * Add a new gadget to the gadget package.
         * @param gadget 
         */
        void addGadget(std::unique_ptr<Gadget> gadget);

        /** 
         * Queries all sensors in the package that have a given capability,
         * and returns their readings.
         * @param capability 
         * @return Optionally returns data from any capable sensors.
         */
        std::optional<GadgetData> getReading(Capability capability) const;

        void blinkAndBeep(int n);

        bool hasCapability(Capability cap) const;
    };
    #endif
}