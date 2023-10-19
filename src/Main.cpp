#include <Arduino.h>

void setup() {
  //Serial.begin(9600); //For debugging purposes only

  /**

  hardwarePackage.setup();
  sensorPackage.setup();

  kernel.setup();

  EEPROM.begin(512);  //Emulates EEPROM by allocating 512 kB from the flash memory

  Wire1.setSDA(PIN_I2C_SDA);
  Wire1.setSCL(PIN_I2C_SCL);


  SPI.setRX(PIN_SPI_RX);
  SPI.setTX(PIN_SPI_TX);
  SPI.setSCK(PIN_SPI_SCK);
  SPI.setCS(PIN_SPI_CS);

  setupLEDs();

  rotarySwitchSetup();

  barometer->begin();
  accelerometer->begin();

  switchStartup();

  delay(FLIGHT_COMPUTER_ARM_DELAY_MS);  //Wait for 10 seconds to allow the rocketeer to prepare for launch before the flight computer is armed.
  //preLaunchStage();                     //Here I store the first second of data into the circular buffers

  launchDetector.begin(LAUNCH_ACCELERATION_THRESHOLD, LAUNCH_ALTITUDE_THRESHOLD);

  logger.begin();
  String logFilename = logger.getNewLogFilename();
  logfile = logger.open(logFilename);


  **/
}

const int BATTERY_LED_PIN = 2;  // Battery indicator LED
const int STATUS_LED_PIN = 26;  // Status LED, used to indicate errors to the user

void setupLEDs() {
  pinMode(BATTERY_LED_PIN, OUTPUT);  // Low battery LED
  pinMode(STATUS_LED_PIN, OUTPUT);   // Status LED
}

void turnOnStatusLED() {
  // Turn on the blue status LED.
  digitalWrite(STATUS_LED_PIN, HIGH);
}

void turnOffStatusLED() {
  // Turn off the blue status LED .
  digitalWrite(STATUS_LED_PIN, LOW);
}

void blinkStatusLED(int n) {  // Blinks the blue status LED every 200 ms
  for (int i = 0; i <= n; i++) {
    digitalWrite(STATUS_LED_PIN, HIGH);
    delay(200);
    digitalWrite(STATUS_LED_PIN, LOW);
    delay(200);
  }
}

void turnOnLowBatteryLED() {
  digitalWrite(BATTERY_LED_PIN, HIGH);
}

void turnOffLowBatteryLED() {
  digitalWrite(BATTERY_LED_PIN, LOW);
}



void loop() {
  setupLEDs();
  turnOnStatusLED();
  delay(500);
  turnOnLowBatteryLED();
  delay(500);
  blinkStatusLED(5);
  // Set the low battery LED if battery voltage is low.
  //setLowBatteryLED();

  //Kernel.think();
  //flightLoop();
}
