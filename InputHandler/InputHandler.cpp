#include "InputHandler.h"

InputHandler::InputHandler ( FaeTheFair *fae , CameraHandler *camera ){
  this->fae = fae;
  this->camera = camera;
}

InputHandler::~InputHandler (){}

bool InputHandler::onKeyPress( unsigned char key , int x , int y ){
  std::string file;
  bool good = true;
  switch (key) {
    case 'w': case 'W':
      this->camera->rotateXPositive();
    break;
    case 's': case 'S':
      this->camera->rotateXNegative();
    break;
    case 'a': case 'A':
      this->camera->rotateYNegative();
    break;
    case 'd': case 'D':
      this->camera->rotateYPositive();
    break;
    case 'q': case 'Q':
      this->camera->rotateZNegative();
    break;
    case 'e': case 'E':
      this->camera->rotateZPositive();
    break;
    case 't': case 'T':
      this->camera->resetRotation();
    break;
    case 'y': case 'Y':
      this->camera->resetPanning();
    break;
    case ' ':
      this->fae->toggleMovement();
    break;
    case 'k': case 'K':
      this->fae->toggleLoop();
    break;
    case 'p': case 'P':
      this->camera->setCurrentPanningAsDefault();
    break;
    case 'o': case 'O':
      this->camera->setCurrentRotationAsDefault();
    break;
    case 'r': case 'R':
      this->fae->restart();
    break;
    case '-': //SHIFT
      this->camera->panFar();
    break;
    case '.': //CTRL
      this->camera->panNear();
    break;
    case 27:
      good = false;
    break;
    case 'l': case 'L':
      file = this->openFileNavigator();
      if( file.size() != 0 ){
        this->fae->readScript(file);
      }
    break;
    default:
      std::cout << "Unkown key: "<< key << " = " << int(key) <<std::endl;
    break;
  }
  return good;
}

void InputHandler::onSpecialKeyPress( int key , int x , int y ){
  switch (key) {
    case GLUT_KEY_UP:
      this->camera->panUp();
    break;
    case GLUT_KEY_DOWN:
      this->camera->panDown();
    break;
    case GLUT_KEY_LEFT:
      this->camera->panLeft();
    break;
    case GLUT_KEY_RIGHT:
      this->camera->panRight();
    break;
    default:
      std::cout << "Unkown special key: "<< key << std::endl;
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
