#include "CircularBuffer.h"

CircularBuffer<float, 100> FilteredAltitudes;
CircularBuffer<float, 100> altitudes;
CircularBuffer<float, 100> accelerations;
CircularBuffer<long, 100> times;

void think() {
  /** The rockit can be in one of four different flight states:
   *  - 1) On the ground, pre-launch.
   *  - 2) Post launch, in mid-flight
   *  - 3) Post launch, in recovery
   *  - 4) Post launch,
   **/


  static bool flightIsOver = false;

  if (flightIsOver) {
    // Beep and blink indefinitely, never return.
    beepnblink();
  }

  barometer->getPressureReading();
  temp = barometer->getTemperatureReading();
  WocketAccelerationData accelerationData = accelerometer->getAccelerationReading();

  altitudeDelta = barometer->getAltitudeDelta();
  filteredAltitudeDelta = barometer->getFilteredAltitudeDelta();

  // Store data to the circular buffer
  if (!launchDetector.launchDetected(acceleration, altitudeDelta)) {
    logPreLaunchData();
  }

  t1 = millis() - t4 - times[0];
  
  //recoveryStage();

  /**
  logfile.print(t1);
  logfile.print(',');
  logfile.print(altitudeDelta);
  logfile.print(',');
  logfile.print(filteredAltitudeDelta);
  logfile.print(',');
  logfile.print(acceleration);
  logfile.print(',');
  logfile.print(event.acceleration.z / 9.81);
  logfile.print(',');
  logfile.println(temp, 1);
  **/

  if (altitudeDelta > altold) {  //Here is where I store the maximum altitude value
    altMax = round(altitudeDelta);
    altold = altMax;
  }

  if (r == 200 && flightIsOver == false) {  //Here I set the rate at which I send data to the uSD card
    r = 0;
    logfile.flush();
  }
  r++;


  if (t1 >= FLIGHT_COMPUTER_TIMEOUT_MS) {
    flightIsOver = true;
    logfile.flush();
    logfile.close();  //After timeout flush the data to the microSD card and close the file
  }
}

void logPreLaunchData() {
  accelerations.push(acceleration);
  altitudes.push(altitudeDelta);
  FilteredAltitudes.push(filteredAltitudeDelta);
  times.push(millis() - t4);  //Circular buffer for time

  for (int i = 0; i <= 99; i++) {        //Saving the buffer allows me to store the data measured before launch.
  /**
    logfile.print(times[i] - times[0]);  //Here times[0] sets the time zero for the time variable
    logfile.print(',');
    logfile.print(altitudes.shift());
    logfile.print(',');
    logfile.print(FilteredAltitudes.shift());
    logfile.print(',');
    logfile.print(accelerations.shift());
    logfile.print(',');
    logfile.print(event.acceleration.z / 9.81);
    logfile.print(',');
    logfile.println(temp, 1);
    **/
  }

  logfile.flush();  //Store data of the 908 ms before launch
}
