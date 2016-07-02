

/*
Class to handle PixyCam, through it's basic analog interface
 can report the x-position of an object, and whether or not an object is detected
*/

#ifndef PixyAnalog_h
#define PixyAnalog_h

#include "Arduino.h"

class PixyAnalog
{
public:
  //Constructor: takes the two pins to use for reading the 
  //analog interface, as well as a 'centerVal', corresponding
  //to the value of analogRead(detectionPin) when an object is
  //dead in front of the camera (on first test, this was 600)
  PixyAnalog(int detectionPin, int xPosPin, int centerVal); 

  //return true if camera detects an object
  boolean detectsObject();

  //returns a value proportional to the x position
  //of the largest detected object in the image
  int objectXPosition();

private:
  int _detectionPin;
  int _xPosPin;
  int _centerVal;
  int _detectionThreshold;
};
#endif
