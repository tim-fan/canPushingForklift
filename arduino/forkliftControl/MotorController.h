

/*
Class to control motors for forklift. 
 Interface to motors is via designated pins for forward, left, right and backward.
 At lowest level, controller can be used to set the pin configuration to move forward
 or backward, and to drive the turning motor left or right. 
 
 Above this it is intended 
 to use a timer to stop driving the turning motor after a short period (don't need to 
 continue driving it after the wheel has been turned.
 
 Above this it is intended to apply some hysteresis to the turning input, such that 
 the turning motor cannot be commanded to switch quickly and repeatedly between left and right
 */

#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"
#include "TimerOne.h"

class MotorController
{
public:
  MotorController();

  //specifies pins to use for motor control, sets them to OUTPUT, and initialises timer
  void attach(int forwardPin, int backwardPin, int leftPin, int rightPin, TimerOne timer, void (*clearTurn)());

  //direction control
  void goLeft();
  void goRight();
  void goForward();
  void goBackward();

  //sets turing pins low
  void clearTurn();

private:
  int _forwardPin;
  int _backwardPin;
  int _leftPin;
  int _rightPin;
  int _turnTime; //time to set turning pins high, in microsec
  
  void (*_clearTurn)();
  TimerOne _timer;  
};




#endif

