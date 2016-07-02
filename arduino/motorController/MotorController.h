

/*
Class to control motors for forklift. 
 Interface to motors is via designated pins for driving the steering left and right, and the
 drive motor forwards and back.

 Takes care that turn motors are only driven long enough to ensure the motor reaches full lock.
 After this, the truck will continue to turn if driven forward, even though the turn motor is off
 */

#ifndef MotorController_h
#define MotorController_h

#include "Arduino.h"

class MotorController
{
public:
  MotorController(); 
  void attach(int forwardPin, int backwardPin, int leftPin, int rightPin);

  //direction control
  void turnLeft();
  void turnRight();
  void changeDirection();
  void goForward();
  void goBackward();
  void stop();

  //blocks subsequent calls to go forward/backward (for testing purposes)
  void disableDrive(); 

  //call this repeatedly when using steer controller
  //(responsible for turning steer motor off)
  void update();

private:
  
  int _forwardPin;
  int _backwardPin;
  int _leftPin;
  int _rightPin;
  boolean _driveEnabled;
  
  enum TurnState
  {
	LEFT,
	RIGHT
  };
  TurnState _turnState;

  unsigned long _turnDuration; //time to set turning pins high, in microsec
  unsigned long _turnStartTime;
  boolean _turnMotorEngaged;

};
#endif
