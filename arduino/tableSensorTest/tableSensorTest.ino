#include <TableSensor.h>


//Basic test for motor controller, turns left and right repeatedly
//Uses timer1 library to call motor controller update function

int rightFrontEdgeSensorPin = A0;                                                                                                                                                                                                                                                  
int leftFrontEdgeSensorPin = A1;                                                                                                                                                                                                                                                   
int rightBackEdgeSensorPin = A2;                                                                                                                                                                                                                                                   
int leftBackEdgeSensorPin = A3; 

int tableSensorThreshold = 500; //out of total analog range 1023

TableSensor rightFrontEdgeSensor(rightFrontEdgeSensorPin, tableSensorThreshold);
TableSensor leftFrontEdgeSensor(leftFrontEdgeSensorPin, tableSensorThreshold);
TableSensor rightBackEdgeSensor(rightBackEdgeSensorPin,tableSensorThreshold);
TableSensor leftBackEdgeSensor(leftBackEdgeSensorPin,tableSensorThreshold);


void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop(){
  //ledState = !ledState;
  //digitalWrite(LED_BUILTIN, ledState);

  //will abbreviate naming of sensors, as follows: rf = rightFront, lb = leftBack, etc.

  //check sensor states
  boolean rfOnTable = rightFrontEdgeSensor.isOnTable();
  boolean lfOnTable = leftFrontEdgeSensor.isOnTable();
  boolean rbOnTable = rightBackEdgeSensor.isOnTable();
  boolean lbOnTable = leftBackEdgeSensor.isOnTable();

  //report sensor states:
  Serial.print(String("rf: ") + String(rfOnTable) + String('\t'));
  Serial.print(String("lf: ") + String(lfOnTable) + String('\t'));
  Serial.print(String("rb: ") + String(rbOnTable) + String('\t'));
  Serial.print(String("lb: ") + String(lbOnTable) + String('\n'));

  //pasue before looping
  delay(200);
}
