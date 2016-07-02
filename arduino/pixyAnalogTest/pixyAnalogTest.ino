#include <PixyAnalog.h>

PixyAnalog pixy(A4,A5, 600);

void setup(){
  Serial.begin(9600);
}

void loop(){
  if (pixy.detectsObject()){
    Serial.println(String("Pixy detects object at x = ") + String(pixy.objectXPosition()));
  }
  else{
    Serial.println("No objects detected");
  }
  
  delay(200);
}
