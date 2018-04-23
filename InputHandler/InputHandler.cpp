#include "InputHandler.h"

InputHandler::InputHandler ( FaeTheFair *fae , CameraHandler *camera ){
  this->fae = fae;
  this->camera = camera;
}

InputHandler::~InputHandler (){}

void InputHandler::onKeyPress( unsigned char key , int x , int y ){
  switch (key) {
    case 'w': case 'W':
      this->camera->rotateUp();
    break;
    case 's': case 'S':
      this->camera->rotateDown();
    break;
    case 'a': case 'A':
      this->camera->rotateLeft();
    break;
    case 'd': case 'D':
      this->camera->rotateRight();
    break;
    case 't': case 'T':
      this->camera->resetRotation();
    break;
    case ' ':
      this->fae->toggleMovement();
    break;
    case 'r': case 'R':
      this->fae->restart();
    break;
    case 'l': case 'L':
      std::string file = this->openFileNavigator();
      if( file.size() != 0 ){
        this->fae->readScript(file);
      }
    break;
  }
}

std::string InputHandler::openFileNavigator(){
  std::string cmd = "zenity --file-selection ./ 2> /dev/null";
  std::string str = this->exec(cmd.c_str());
  const std::string pattern = " \f\n\r\t\v";
  return str.substr(0,str.find_last_not_of(pattern) + 1);
}

std::string InputHandler::exec(const char* cmd) {
    FILE* pipe = popen(cmd, "r");
    if (!pipe) return "";
    char buffer[128];
    std::string result = "";
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe) != NULL)
            result += buffer;
    }
    pclose(pipe);
    return result;
}
