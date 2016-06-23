


#include "Arduino.h"
#include "Camera.h"

#define NUM_RETRIES 10 //how many calls to getBlocks before returning zero



void Camera::init()
{
  _pixy.init();
  refresh();
}

void Camera::refresh()
{
  _numBlocks = 0;
  int i = 0;
  while ((_numBlocks == 0) && (i < NUM_RETRIES))
  {
    _numBlocks = _pixy.getBlocks();
    i++;
  }  

  //digitalWrite(LED_BUILTIN, LOW);
  if (_numBlocks)
    seesBlob = true;
  else
    seesBlob = false;
  if (_numBlocks > 0)
  {
    blobX = _pixy.blocks[0].x;
    blobY = _pixy.blocks[0].y;
  }
}


