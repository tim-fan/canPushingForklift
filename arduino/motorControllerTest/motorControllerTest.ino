
#include <MotorController.h>
#include <TimerOne.h>

//Basic test for motor controller, turns left and right repeatedly
//Uses timer1 library to call motor controller update function

int forwardPin = 11;
int backwardPin = 10;
int leftPin = 6;
int rightPin = 8;

boolean ledState = false;

//Ensure update is called repeatedly by initialising a global motor controller,
//and calling the update method in an ISR
MotorController motorController;

void updateMotorController(void){
  motorController.update();
}

//define a few different test sequences. Call from 'loop' to activate
void testAllDirections(){
  //runs steering and drive in all possible directions  
  ledState = !ledState;
  digitalWrite(LED_BUILTIN, ledState);

  motorController.stop();
  motorController.turnLeft();
  delay(2000);
  motorController.turnRight();
  delay(2000);
  
  motorController.goForward();
  motorController.turnLeft();
  delay(2000);
  motorController.turnRight();
  delay(2000);

  motorController.goBackward();
  motorController.turnLeft();
  delay(2000);
  motorController.turnRight();
  delay(2000);

}

void testChangeDirection(){
  //test the motor controller's changeDirection  
  motorController.changeDirection();
  delay(2000);
}


void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  motorController.attach(forwardPin, backwardPin, leftPin, rightPin);
  Timer1.initialize();
  Timer1.attachInterrupt(updateMotorController, 200000); //update motor controller at 50 Hz
}

void loop(){
//  testAllDirections();
  testChangeDirection();
}
