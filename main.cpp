#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>

#include <exception>

#include "./Juan/Juan.h"
#include "./Vector3D/Vector3D.h"
#include "./Fae/Fae.h"

FaeTheFair* s = new FaeTheFair();

int timeout = 1000/30;

std::string filePath="./res/inputFile.in";

float x = -80;
float z = -60;
float dz = 1.0f;
float dx = 1.0f;
bool zMove = true;

void Timer( int i ){
  if( zMove ){
    z += dz;
    if( dz > 0.0 && z >= 160 ){
      dz = -dz;
      zMove = !zMove;
    }
    else if( dz < 0.0 && z <= -60){
      dz = -dz;
      zMove = !zMove;
    }
  }else{
    x += dx;
    if( dx > 0.0 && x >= 80 ){
      dx = -dx;
      zMove = !zMove;
    }else if( dx < 0.0 && x <= -80 ){
      dx = -dx;
      zMove = !zMove;
    }
  }
  if( s->isMoving() ){
    s->nextFrame();
  }
  glutPostRedisplay();
  glutTimerFunc( timeout, Timer, 0);
}

void init(){

  s->readScript(filePath);

  glClearColor(0.0, 0.0, 0.0, 1.0); // Set background (clear) color to black
  glEnable( GL_DEPTH_TEST );
  glutTimerFunc(0, Timer, 0);
}

void display(){

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Vector eye(x,90,z);
  //Vector center(0,20,20);
  Vector center = s->getPoint(Tag::SACR);
  Vector up( 0.0 , 1.0 , 0.0 );
  Juan::setCamera( eye , center , up );
  Juan::drawStage();
  s->draw();

  glutSwapBuffers();

}

void reshape( int width , int height ){
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0f, (GLfloat)width/(GLfloat)height, 1.0f, 1000.0f);
  glMatrixMode(GL_MODELVIEW);
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
  glutMainLoop();


  return 0;
}
