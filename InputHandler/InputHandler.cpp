#include "InputHandler.h"

InputHandler::InputHandler ( FaeTheFair *fae ){
  this->fae = fae;
}

InputHandler::~InputHandler (){}

void InputHandler::onKeyPress( unsigned char key , int x , int y ){
  switch (key) {
    case ' ':
      this->fae->toggleMovement();
    break;
    case 'r': case 'R':
      this->fae->restart();
    break;
  }
}
