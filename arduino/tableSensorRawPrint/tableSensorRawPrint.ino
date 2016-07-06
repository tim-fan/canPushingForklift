#include <TableSensor.h>

// Simple sketch, prints values from table sensors
// Writen for the purpose of choosing threshold values for the table sensors

// Define analog pins to use (assumed to be attached to table sensors)
int pin0 = A0;
int pin1 = A1;
int pin2 = A2;
int pin3 = A3;


void setup(){
  Serial.begin(9600);
  pinMode(pin0, INPUT);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);
  pinMode(pin3, INPUT);
}

void loop(){

  //report sensor readings as .csv:
  Serial.print(String(analogRead(A0)) + String(','));
  Serial.print(String(analogRead(A1)) + String(','));
  Serial.print(String(analogRead(A2)) + String(','));
  Serial.print(String(analogRead(A3)) + String(','));
  Serial.print(String('\n'));

  //pasue before looping
  delay(200);
}
