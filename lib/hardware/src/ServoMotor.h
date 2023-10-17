#ifndef ROCKIT_SERVO_MOTOR_H
#define ROCKIT_SERVO_MOTOR_H

#include <Servo.h>

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
