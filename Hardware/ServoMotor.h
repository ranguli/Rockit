#ifndef ROCKIT_SERVO_MOTOR_H
#define ROCKIT_SERVO_MOTOR_H

#include <Servo.h>

extern const int SERVO_1_PIN;
extern const int SERVO_2_PIN;
extern const int SERVO_POWER_SAVING_TIMEOUT_MS;
extern const int SERVO_DELAY_MS;

// To prevent a current spike from moving both servos simulataneously, 
// we wait inbetween moving the 1st and 2nd servo motor.
extern const int SERVO_CURRENT_SPIKE_DELAY_MS;

class ServoMotor {
private:
    Servo servo;             
    int pin;           
    int id;                  
    int startPosition;       
    int endPosition;
      
public:
    void begin(int pin, int id, int startPosition, int endPosition); 
    void moveToStartPosition();
    void moveToEndPosition();

    int getPin();
    int getId();
    int getStartPosition();
    int getEndPosition();

    void setId(int newId);
    void setStartPosition(int newStart);
    void setEndPosition(int newEnd);

    bool isAttached();
    void attach();
    void detach();
};

Servo servo1;
Servo servo2;


#endif // ROCKIT_SERVO_MOTOR_H
