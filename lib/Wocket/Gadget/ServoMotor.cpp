#include "Servos.h"
#include "ServoMotor.h"

void ServoMotor::begin(int pin, int id, int startPosition, int endPosition) {
    this->pin = pin;
    this->id = id;
    this->startPosition = startPosition;
    this->endPosition = endPosition;
}

int ServoMotor::getStartPosition() const {
    return startPosition;
}

void ServoMotor::setStartPosition(int newStart) {
    startPosition = newStart;
}

// Method to move the servo to its start position
void ServoMotor::moveToStartPosition() {
    servo.write(startPosition);
}

int ServoMotor::getEndPosition() const {
    return endPosition;
}

void ServoMotor::setEndPosition(int newEnd) {
    endPosition = newEnd;
}

// Method to move the servo to its end position
void ServoMotor::moveToEndPosition() {
    servo.write(endPosition);
}

// Getter methods for class members if needed
int ServoMotor::getPin() const {
    return pin;
}

int ServoMotor::getId() const {
    return id;
}

// Setter methods if needed
void ServoMotor::setId(int newId) {
    id = newId;
}

bool ServoMotor::isAttached() {
    return attached;
}

void ServoMotor::attach() {
    servo.attach();
}

void ServoMotor::detach() {
    servo.detach();
}
