#include "Arduino.h"
#include "MotorController.h"

MotorController::MotorController() 
{
  _turnDuration = 400000; //time (in uS) to hold turining pin high
}

void MotorController::attach(int forwardPin, int backwardPin, int leftPin, int rightPin)
{
  _forwardPin = forwardPin;
  _backwardPin = backwardPin;
  _leftPin = leftPin;
  _rightPin = rightPin;
  
  pinMode(_forwardPin, OUTPUT);
  pinMode(_backwardPin, OUTPUT);
  pinMode(_leftPin, OUTPUT);
  pinMode(_rightPin, OUTPUT);  
}

void MotorController::turnLeft()
{
  if (_turnState != LEFT){
    digitalWrite(_rightPin, LOW);
    digitalWrite(_leftPin, HIGH);
    _turnStartTime = micros();
    _turnMotorEngaged = true;
    _turnState = LEFT;
  }
}

void MotorController::turnRight()
{
  if (_turnState != RIGHT){
    digitalWrite(_leftPin, LOW);
    digitalWrite(_rightPin, HIGH);
    _turnStartTime = micros();
    _turnMotorEngaged = true;
    _turnState = RIGHT;
  }
}

void MotorController::changeDirection()
{
 if (_turnState == LEFT){
   turnRight();
 }
 else{
   turnLeft();
 }
}

void MotorController::goForward()
{
  digitalWrite(_backwardPin, LOW);
  digitalWrite(_forwardPin, HIGH);
}

void MotorController::goBackward()
{
  digitalWrite(_forwardPin, LOW);
  digitalWrite(_backwardPin, HIGH);
}

void MotorController::stop()
{
  digitalWrite(_forwardPin, LOW);
  digitalWrite(_backwardPin, LOW);
}

void MotorController::update()
{
  //stop driving the turn motor, if has been driven for long enough
  if (_turnMotorEngaged){
    unsigned long elapsedTurnTime = micros() - _turnStartTime;
    if (elapsedTurnTime > _turnDuration){
      digitalWrite(_leftPin, LOW);
      digitalWrite(_rightPin,LOW);
      _turnMotorEngaged = false;
    }
  }
}

