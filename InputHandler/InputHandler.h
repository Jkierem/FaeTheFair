#ifndef __INPUT__H__
#define __INPUT__H__

#include "../Fae/Fae.h"

/*
This class is almost useless. Just used to remove logic
from the main function as to clean up code.
*/
class InputHandler {
private:
  FaeTheFair *fae;

public:
  InputHandler ( FaeTheFair *f );
  virtual ~InputHandler ();

  void onKeyPress( unsigned char key , int x , int y );
};

typedef InputHandler Input;

#endif
