#include <TableSensor.h>
#include <MotorController.h>

int forwardPin = 11;
int backwardPin = 10;
int leftPin = 6;
int rightPin = 8;

MotorController motorController;

int rightFrontEdgeSensorPin = A0;
int leftFrontEdgeSensorPin = A1;
int rightBackEdgeSensorPin = A2;
int leftBackEdgeSensorPin = A3;

int tableSensorThreshold = 500; //out of total analog range 1023

TableSensor rightFrontEdgeSensor(rightFrontEdgeSensorPin, tableSensorThreshold);
TableSensor leftFrontEdgeSensor(leftFrontEdgeSensorPin, tableSensorThreshold);
TableSensor rightBackEdgeSensor(rightBackEdgeSensorPin, tableSensorThreshold);
TableSensor leftBackEdgeSensor(leftBackEdgeSensorPin, tableSensorThreshold);
enum MotionState
{
  CHASE_CANS,
  AVOID_FORWARD_EDGE,
  AVOID_BACKWARD_EDGE
};

MotionState motionState = CHASE_CANS;

unsigned long currentStateStartTime;

void setup() {
  motorController.attach(forwardPin, backwardPin, leftPin, rightPin);
  Serial.begin(9600);
  Serial.println("Forklift controller begin");
}

void printState(MotionState state){
  switch(state)
  {
    case CHASE_CANS:
      Serial.println("State: Chase cans");
      break;
    case AVOID_FORWARD_EDGE:
      Serial.println("State: avoiding forward edge");
      break;
    case AVOID_BACKWARD_EDGE:
      Serial.println("State: avoiding backward edge");
      break;
  }
}

void loop() {
  //read inputs:
  
  //will abbreviate naming of sensors, as follows: rf = rightFront, lb = leftBack, etc.
  boolean rfOnTable = rightFrontEdgeSensor.isOnTable();
  boolean lfOnTable = leftFrontEdgeSensor.isOnTable();
  boolean rbOnTable = rightBackEdgeSensor.isOnTable();
  boolean lbOnTable = leftBackEdgeSensor.isOnTable();
  unsigned long timeInCurrentState = millis() - currentStateStartTime;

  //detect events:
  boolean frontSensorOffTable = !(rfOnTable && lfOnTable); 
  boolean backSensorOffTable = !(rbOnTable && lbOnTable);
  
  //next state logic:
  MotionState nextMotionState = motionState;
  switch(motionState)
  {
    case CHASE_CANS:
      if (frontSensorOffTable){
        nextMotionState = AVOID_FORWARD_EDGE;
      }
      else {
        nextMotionState = CHASE_CANS;
      }
      break;

    case AVOID_FORWARD_EDGE:
      if (frontSensorOffTable){
        nextMotionState = AVOID_FORWARD_EDGE;
      }
      else if (backSensorOffTable){
        nextMotionState = AVOID_BACKWARD_EDGE;
      }
      else if (timeInCurrentState > 2000){
        nextMotionState = CHASE_CANS;
      }
      break;

    case AVOID_BACKWARD_EDGE:
      if (frontSensorOffTable){
        nextMotionState = AVOID_FORWARD_EDGE;
      }
      else if (backSensorOffTable){
        nextMotionState = AVOID_BACKWARD_EDGE;
      }
      else if (timeInCurrentState > 1000){
        nextMotionState = CHASE_CANS;
      }
      break;
  }

  if (nextMotionState != motionState){
    motionState = nextMotionState;
    printState(motionState);
    currentStateStartTime = millis();
  }

  //state outputs:
  switch(motionState)
  {
    case CHASE_CANS:
      // go forward, try to push cans off table
      motorController.goForward();
      break;

    case AVOID_FORWARD_EDGE:
      // backup and turn away from edge
      motorController.goBackward();
      if (!rfOnTable){
        motorController.turnRight();
      }
      else if (!lfOnTable){
        motorController.turnLeft();
      }
      break;

    case AVOID_BACKWARD_EDGE:
      // move forward and away from edge
      motorController.goForward();
      if (!rfOnTable){
        motorController.turnLeft();
      }
      else if (!lfOnTable){
        motorController.turnRight();
      }
      break;
  }
}
