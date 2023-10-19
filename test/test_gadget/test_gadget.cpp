#include <Arduino.h>
#include <unity.h>

#include "Gadget.h"
  
Wocket::Gadget gadget;

void setUp(void) {
  gadget = Wocket::Gadget();
  // set stuff up here
}

void tearDown(void) {

}

void test_function_should_doBlahAndBlah(void) {
    gadget.setCapabilities(static_cast<uint32_t>(Wocket::Gadget::Capability::ACCELERATION) |
                             static_cast<uint32_t>(Wocket::Gadget::Capability::TEMPERATURE) |
                             static_cast<uint32_t>(Wocket::Gadget::Capability::PRESSURE));
}

void test_function_should_doAlsoDoBlah(void) {
  // more test stuff
}

int runUnityTests(void) {
  UNITY_BEGIN();
  RUN_TEST(test_function_should_doBlahAndBlah);
  RUN_TEST(test_function_should_doAlsoDoBlah);
  return UNITY_END();
}

void setup() {
  // Wait ~2 seconds before the Unity test runner
  // establishes connection with a board Serial interface
  delay(2000);

  runUnityTests();
}

void loop() {}