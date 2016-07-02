#include "Arduino.h"
#include "PixyAnalog.h"

PixyAnalog::PixyAnalog(int detectionPin, int xPosPin, int centerVal)
{
  _detectionPin = detectionPin;
  _xPosPin = xPosPin;
  _centerVal = centerVal;
  _detectionThreshold = 500;
  pinMode(_detectionPin, INPUT);
  pinMode(_xPosPin, INPUT);
}

boolean PixyAnalog::detectsObject()
{
  return analogRead(_detectionPin) > _detectionThreshold;
}

int PixyAnalog::objectXPosition()
{
  return analogRead(_xPosPin) - _centerVal;
}
