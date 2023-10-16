#include "Servos.h"

//Servos
const int SERVO_1_PIN = 28;
const int SERVO_2_PIN = 27;
const int SERVO_POWER_SAVING_TIMEOUT_MS = 2000;
const int SERVO_DELAY_MS = 500;
const int SERVO_CURRENT_SPIKE_DELAY_MS = 100;

class ServoMotor {
private:
    Servo servo;             
    int pin;           
    int id;                  
    int startPosition;       
    int endPosition;
    
public:
    void begin(int pin, int id, int startPosition, int endPosition) {
        this->pin = pin;
        this->id = id;
        this->startPosition = startPosition;
        this->endPosition = endPosition;
    }

    int getStartPosition() const {
        return startPosition;
    }

    void setStartPosition(int newStart) {
        startPosition = newStart;
    }

    // Method to move the servo to its start position
    void moveToStartPosition() {
        servo.write(startPosition);
    }

    int getEndPosition() const {
        return endPosition;
    }

    void setEndPosition(int newEnd) {
        endPosition = newEnd;
    }

    // Method to move the servo to its end position
    void moveToEndPosition() {
        servo.write(endPosition);
    }

    // Getter methods for class members if needed
    int getPin() const {
        return pin;
    }

    int getId() const {
        return id;
    }

    // Setter methods if needed
    void setId(int newId) {
        id = newId;
    }

    bool isAttached() {
      return attached;
    }

    void attach() {
      servo.attach();
    }

    void detach() {
      servo.detach();
    }
};
