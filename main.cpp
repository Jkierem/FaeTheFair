#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

#include "./config/config.h"
#include "./CameraHandler/CameraHandler.h"
#include "./Fae/Fae.h"
#include "./InputHandler/InputHandler.h"
#include "./Juan/Juan.h"
#include "./LightHandler/LightHandler.h"
#include "./Vector3D/Vector3D.h"

config::SimConfig simConfig = config::getSimConfig();
config::CameraConfig camConfig = config::getCameraConfig();

Camera *camera = new Camera(camConfig);
FaeTheFair *sim = new FaeTheFair(simConfig);
Input *input = new Input(sim,camera,simConfig.inputDebug);
Light *light = new Light();

void Timer( int i ){
  if( sim->isMoving() ){
    sim->nextFrame();
  }
  glutPostRedisplay();
  glutTimerFunc( sim->getTimeout(), Timer, 0);
}

void printInstructions(){

  std::cout <<
  "User Interaction: \n" <<
  "  Space Bar: start, stop and resume the sim. The default state is stop\n" <<
  "  R Key: restart sim.\n" <<
  "  L Key: load a sim file using zenity*.\n" <<
  "  W,S Keys: rotation on X axis.\n" <<
  "  A,D Keys: rotation on Y axis.\n" <<
  "  Q,E Keys: rotation on Z axis.\n" <<
  "  Arrow keys: panning on XY plane.\n" <<
  "  - Key: panning to positive Z plane.\n" <<
  "  . Key: panning to negative Z plane.\n" <<
  "  T Key: reset rotation to default rotation.\n" <<
  "  Y Key: reset panning to default panning.\n" <<
  "  O key: save current rotation as default rotation.\n" <<
  "  P Key: save current panning as default panning.\n" <<
  "  K Key: toggle simulation loop.\n" <<
  "  F Key: cycle frame rates. They are 15, 30 and 60 fps. The default is 30 fps.\n" <<
  "  ESC Key: exit program.\n"<<
  "*Requires zenity and unix based os or else the program will crash. "<<
  "Files without the proper structure will also cause a crash."
   << std::endl;
}

void init(){
  printInstructions();
  sim->readScript(simConfig.filePath);

  light->enableLighting();
  glShadeModel(GL_SMOOTH);
  light->enableLight(0);
  light->setPos(0, Vector(0,1,1));
  light->refresh();

  glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
  glEnable( GL_DEPTH_TEST );
  glutTimerFunc(0, Timer, 0);
}

void display(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  Vector sacr = sim->getPoint(Tag::SACR);
  camera->setRelativeEye(Vector(0,0,-3000));
  camera->lookAt(sacr);
  camera->update();

  sim->draw();

  glutSwapBuffers();

}

void reshape( int width , int height ){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 6000.0f);
  glMatrixMode(GL_MODELVIEW);
}

void keyboard( unsigned char key , int x , int y ){
  if( !input->onKeyPress(key,x,y) ){
    exit(0);
  }
}

void keyboardSpc( int key , int x , int y ){
  input->onSpecialKeyPress(key,x,y);
}

int main(int argc, char *argv[]) {

  //Initial display and window config
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowPosition(100, 100);
  glutInitWindowSize(600,600);
  glutCreateWindow("Gait Lab Sim");

  init();

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboardSpc);
  glutMainLoop();


  return 0;
}
