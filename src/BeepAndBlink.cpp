#include <Arduino.h>

#include "Config.h"

#include "BeepAndBlink.h"
#include "Hardware/LEDs.h"
#include "Hardware/PiezoBuzzer.h"

/**
void altitudeToDigits(){ // Convert altitude to digits
  int altMaxDig[4] = {}; //Max altitude digits

  for (int i=0; i<4; i++){
    int rmnd = altMax % 10; // This is the remainder
    altMaxDig[i] = rmnd;
    altMax = altMax / 10;
  }
}
**/
void beepnblink(){
  static int p = 0;

  if (initVar == true && flightIsOver == false){

    if (p<30){
      turnOnStatusLED();
      turnOnPiezoBuzzer();
    }
  
    else if (p == 30){
      turnOffStatusLED();
      turnOffPiezoBuzzer();
    }

    else if (p == 400){
      p = 0;
    }
  p++;
  }

  else if (initVar == false && flightIsOver == false){ //This is necesary because if p<30 after launch is detected the LED and the piezo buzzer will be stuck in ON mode.
    turnOffStatusLED();
    
    // This conditional is the opposite of 
    if (PIEZO_BUZZER_ENABLED == false){
      analogWrite(PIEZO_BUZZER_PIN, 0);
    }
  }

  else if (initVar == false && flightIsOver == true){ //After timeout blink and beep the maximum altitude in meters
    //altitudeToDigits(); //Convert the maximum altitude to digits
    while(1){
      for (int i=3; i>-1; i--){
        //blinknbeep(altMaxDig[i]); // Beep and blink the altitude digits
        delay(700); // 0.5s pause in between the beeps and blinks
        if (i == 0){
          sleep_ms(10000); // Sleep for 10 seconds to save battery
        }
      }
    }
  }
}

void blinknbeep(int n) { // Blinks the blue LED every 250 ms and makes the buzzer beep
    for (int i=0; i<n; i++){
      turnOnStatusLED();
      turnOnPiezoBuzzer();
      delay(250);
      
      turnOffStatusLED();
      turnOffPiezoBuzzer();
      delay(250);
    }
}
