#include <EEPROM.h>

#include "State.h"
#include "Constants.h"
#include "Servos.h"
#include "Pins.h"

void timerRecovery() {
  int deployTime = EEPROM.read(ADDRESS_TIMER_FLIGHT_MODE_DEPLOY_TIME);
  int servo2DeployTime = EEPROM.read(ADDRESS_SERVO_2_DEPLOYMENT_TIME);

  int timeThreshold = 1000 * deployTime + 908; //Here the 908 ms correspond to the time covered by the circular buffer

  if (t1 >= (timeThreshold)) {                      
    servo1.attach();
    servo1.moveToEndPosition();

    if (timer == true && t1 >= (timeThreshold + SERVO_POWER_SAVING_TIMEOUT)) {  //We disable the servo after 2 seconds to save power
      servo1.detach();
    }

    if (t1 >= (timeThreshold + SERVO_DELAY_MS * servo2DeployTime + SERVO_CURRENT_SPIKE_DELAY_MS)) {
      servo2.write(EEPROM.read(ADDRESS_SERVO_2_END_POSITION));
      servo2.attach(PIN_SERVO_2);
      timer = false;
    }

    if (t1 >= (timeThreshold + SERVO_DELAY_MS * servo2DeployTime + SERVO_CURRENT_SPIKE_DELAY_MS + SERVO_POWER_SAVING_TIMEOUT_MS)) {  //We disable the servo after 2 seconds to save power
      servo2.detach();
      timer = false;
    }
  }
}

void automaticRecovery() {
  if ((filteredAltitudeDelta - altold) < -0.01) {
    n++;
    if (n == 4 && deploy == false) {
      deploy = true;
      tconfig = t1;
    }
  }

  else if ((filteredAltitudeDelta - altold) >= 0 && deploy == false) {
    n = 0;
  }

  const int parachuteDeploymentTimeAuto = EEPROM.read(ADDRESS_AUTO_FLIGHT_MODE_DEPLOY_TIME_MS);
  const int deployTime = SERVO_DELAY_MS * parachuteDeploymentTimeAuto;

  // Servo 1
  if (deploy == true && (t1 - tconfig) >= deployTime) {
    servo1.write(EEPROM.read(3));
    servo1.attach(PIN_SERVO_1);
    if (deploy == true && (t1 - tconfig) >= (deployTime + SERVO_POWER_SAVING_TIMEOUT_MS)) {  //We disable the servo after 2 seconds to save power
      servo1.detach();
    }
  }
  const int servo2DeploymentTime = EEPROM.read(ADDRESS_SERVO_2_DEPLOY_TIME_MS);

  // Servo 2
  if (deploy == true && (t1 - tconfig) >= (deployTime + servo2DeploymentTime)) {
      servo2.write(EEPROM.read(5));
      servo2.attach(PIN_SERVO_2);
      deploy = false;
      if (deploy == true && (t1 - tconfig) >= (deployTime + servo2DeploymentTime) + SERVO_POWER_SAVING_TIMEOUT_MS) { //We disable the servo after 2 seconds to save power
          servo2.detach();
        }
  }
}

void recoveryStage() {
  if (timer == true) {
    timerRecovery();
  } else if (automatic == true) {
    automaticRecovery();
  }
}
