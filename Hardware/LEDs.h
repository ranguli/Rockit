#ifndef ROCKIT_LEDS_H
#define ROCKIT_LEDS_H

// LEDs
extern const int PIN_BATTERY_LED;
extern const int PIN_STATUS_LED;

void setupLEDs();
void turnOnStatusLED();
void turnOffStatusLED();
void blinkStatusLED(int n);

#endif // ROCKIT_LEDS_H