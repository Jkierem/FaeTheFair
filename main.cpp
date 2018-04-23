#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

#include "./Juan/Juan.h"
#include "./Vector3D/Vector3D.h"
#include "./Fae/Fae.h"
#include "./CameraHandler/CameraHandler.h"
#include "./InputHandler/InputHandler.h"

FaeTheFair *sim = new FaeTheFair();
Camera *camera = new Camera(Vector(-90,0,0));
Input *input = new Input(sim,camera);

int timeout = 1000/30;

std::string filePath="./res/inputFile.in";

float x = -80;
float z = -60;
float dz = 1.0f;
float dx = 1.0f;
bool zMove = true;

void Timer( int i ){
  if( sim->isMoving() ){
    sim->nextFrame();
  }
  glutPostRedisplay();
  glutTimerFunc( timeout, Timer, 0);
}

void init(){

  sim->readScript(filePath);
  //camera->rotateX(-90); //Setting base rotation
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
  //Juan::drawStage();
  sim->draw();

  glutSwapBuffers();

}

void reshape( int width , int height ){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 5000.0f);
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
