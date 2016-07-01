

/*
Class to handle table sensors. 
 Reads a given analog pin, and will report 'on table' if the analog value of that pin passes
 a threshold test
 
*/

#ifndef TableSensor_h
#define TableSensor_h

#include "Arduino.h"

class TableSensor
{
public:
  TableSensor(int sensorPin, int threshold); 

  boolean isOnTable();

private:
  
  int _sensorPin;
  int _threshold;
};
#endif
