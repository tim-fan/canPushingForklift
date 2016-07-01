#include "Arduino.h"
#include "TableSensor.h"

TableSensor::TableSensor(int sensorPin, int threshold)
{
  _sensorPin = sensorPin;
  _threshold = threshold;
  pinMode(_sensorPin, INPUT);
}

boolean TableSensor::isOnTable()
{
  return analogRead(_sensorPin) < _threshold;
}
