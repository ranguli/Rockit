#ifndef ROCKIT_SERVOS_H
#define ROCKIT_SERVOS_H

#include <Servo.h>

class Servos {
private:
    Servo servo;             
    const int pin;           
    int id;                  
    int startPosition;       
    int endPosition;
      
public:
    void begin(int p, int i, int start, int end);

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

#endif // ROCKIT_SERVOS_H
