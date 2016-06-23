

#include "Arduino.h"
#include "MotorController.h"
#include <TimerOne.h>

MotorController::MotorController() {}

void MotorController::attach(int forwardPin, int backwardPin, int leftPin, int rightPin, TimerOne timer, void (*clearTurn)())
{
  _forwardPin = forwardPin;
  _backwardPin = backwardPin;
  _leftPin = leftPin;
  _rightPin = rightPin;
  _timer = timer;
  _clearTurn = clearTurn;
  _turnTime = 400000; //time (in uS) to hold turining pin high
  
  pinMode(_forwardPin, OUTPUT);
  pinMode(_backwardPin, OUTPUT);
  pinMode(_leftPin, OUTPUT);
  pinMode(_rightPin, OUTPUT);  
  _timer.initialize();
}

void MotorController::goLeft()
{
  //set left pin high, use timer interupt to set low again after a certain amount of time
  clearTurn(); //don't want to risk setting left and right high at same time
  _timer.detachInterrupt();
  digitalWrite(_leftPin, HIGH);
  digitalWrite(13, HIGH);
  _timer.attachInterrupt(_clearTurn, _turnTime);
}


void MotorController::clearTurn()
{
  _clearTurn();
}


