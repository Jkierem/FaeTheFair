#ifndef __INPUT__H__
#define __INPUT__H__

#include <string>
#include <iostream>
#include <stdlib.h>

#include "../Fae/Fae.h"
#include "../CameraHandler/CameraHandler.h"

/*
This class is almost useless. Just used to remove logic
from the main function as to clean up code.
*/
class InputHandler {
private:
  FaeTheFair *fae;
  CameraHandler *camera;

public:
  InputHandler ( FaeTheFair *fae , CameraHandler *camera);
  virtual ~InputHandler ();

  bool onKeyPress( unsigned char key , int x , int y );
  void onSpecialKeyPress( int key , int x , int y );
  std::string openFileNavigator();
  std::string exec(const char* cmd);
};

typedef InputHandler Input;

#endif
