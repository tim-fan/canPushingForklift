#include "TimerOne.h"
#include "PixyUART.h"
#include "Camera.h"


Camera camera;

int forward = 11;
int backward = 10;
int left = 6;
int right = 8;
int rightFrontEdgeSensor = A0;
int leftFrontEdgeSensor = A1;
int rightBackEdgeSensor = A2;
int leftBackEdgeSensor = A3;
long turnTime = 100000;
int blobTargetHeight = 10;
int currentTurn;

void clearTurn(){
  //digitalWrite(LED_BUILTIN, LOW);
  digitalWrite(left, LOW);  
  digitalWrite(right, LOW);
}

void turn(int directionPin)
{
  clearTurn();  
  Timer1.detachInterrupt();
  
  digitalWrite(directionPin, HIGH);
  //digitalWrite(LED_BUILTIN, HIGH);
  
  Timer1.attachInterrupt(clearTurn, turnTime);
  currentTurn = directionPin;
}

void reverseTurn(void)
{
  if (currentTurn == left)
  {
    turn(right);
  }
  else
  {
    turn(left);
  }
}

void move(int directionPin)
{
  if (directionPin == forward)
  {
    digitalWrite(backward, LOW);
    digitalWrite(forward, HIGH);    
  }
  else
  {
    digitalWrite(forward, LOW);
    digitalWrite(backward, HIGH);
  }  
}
void stopMoving()
{
    digitalWrite(forward, LOW);
    digitalWrite(backward, LOW);
}

boolean edgeSensorOnTable(int sensorPin)
{
  int sensorThresholdPercentage = 50;
  int sensorVal = analogRead(sensorPin);
  int sensorPercent = map(sensorVal, 0, 1023, 0, 100); 
  boolean sensorOnTable = sensorPercent < sensorThresholdPercentage;
  return sensorOnTable;
}

void turnTest()
{
  turn(left);
  delay(2000);
  turn(right);
  delay(2000);
}

void moveTest()
{
  move(forward);
  delay(2000);
  move(backward);
  delay(2000);
  stopMoving();
}

void setup() {
  Timer1.initialize();
  pinMode(forward,OUTPUT);
  pinMode(backward,OUTPUT);
  pinMode(left,OUTPUT);
  pinMode(right,OUTPUT);
  pinMode(LED_BUILTIN ,OUTPUT);
  //Serial.begin(9600);
  //Serial.println("Forklift debug info:");
  stopMoving();
  //turn(right);
  delay(2000);
  //move(forward);
  //camera.init(); // note: this initialises serial to baud = 19200
}

void loop() {
  turnTest();
  moveTest();
  // check table sensors
  /*
  boolean rightFrontOnTable = edgeSensorOnTable(rightFrontEdgeSensor);  
  boolean leftFrontOnTable = edgeSensorOnTable(leftFrontEdgeSensor);
  boolean rightBackOnTable = edgeSensorOnTable(rightBackEdgeSensor);  
  boolean leftBackOnTable = edgeSensorOnTable(leftBackEdgeSensor);
  int numSensorsOnTable = int(rightFrontOnTable) + int(leftFrontOnTable) + int(rightBackOnTable) + int(leftBackOnTable);
  boolean allOnTable = (numSensorsOnTable == 4);
  boolean moreThanOneOffTable = (numSensorsOnTable < 3);
  boolean allOffTable = (numSensorsOnTable == 0);
  */
  
  /*
  // check camera
  camera.refresh();
  uint16_t blobX = camera.blobX;
  uint16_t blobY = camera.blobY;
  
  
  if (!camera.seesBlob || !allOnTable)
    stopMoving();
  else 
  {
    move(forward);
    if (blobX < 319/2)
      turn(left);
    else
      turn(right);
  }
 
  
  //turnTest();
  Serial.print(blobX);
  Serial.print("\t");
  Serial.println(blobY);
  digitalWrite(LED_BUILTIN, camera.seesBlob);
  //delay(50);
  //digitalWrite(LED_BUILTIN, moreThanOneOffTable);
  //digitalWrite(LED_BUILTIN, HIGH);
  //delay(100);
   */
  /*
  Serial.print("rightFrontOnTable: ");
  Serial.print(rightFrontOnTable, BIN);
  
  Serial.print("\tleftFrontOnTable:  ");
  Serial.print(leftFrontOnTable, BIN);
  
  Serial.print("\trightBackOnTable:  ");
  Serial.print(rightBackOnTable, BIN);
  
  Serial.print("\tleftBackOnTable:   ");
  Serial.println(leftBackOnTable, BIN);
  */

  /*
  if (allOffTable)
  {
    stopMoving();
  }
  else if (!rightFrontOnTable)
  {
    turn(right);
    move(backward); 
  }
  else if (!leftFrontOnTable)
  {
    turn(left);
    move(backward);
  }
  else if (!rightBackOnTable)
  {
    turn(left);
    move(forward);
  }
  else if (!leftBackOnTable)
  {
    turn(right);
    move(forward);
  }

  */
  
}
