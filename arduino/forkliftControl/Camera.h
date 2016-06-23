

/*
Wrapper around pixy cam, to give an easier interface. 
At all times will only be interested in the largest block.
This object will be used to determine if there is a block, 
and if so what its x and y coordinates are
 */

#ifndef Camera_h
#define Camera_h

#include "Arduino.h"
#include "PixyUART.h"

class Camera
{
public:
  
  //prepares serial comms. to the camera
  void init();

  //get latest info from camera
  void refresh();
  bool seesBlob;
  uint16_t blobX;
  uint16_t blobY;

private:
  PixyUART _pixy;
  uint16_t _numBlocks;
};
#endif

