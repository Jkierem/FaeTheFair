#include "Juan.h"
#include <iostream>
#include <cmath>

//--------- Utility funks --------------//
void Juan::translate( Vector t ){
  glTranslatef( t.getX() , t.getY() , t.getZ() );
}

void Juan::scale( Vector s ){
  glScalef( s.getX() , s.getY() , s.getZ() );
}

void Juan::rotate( float angle , Vector v){
  glRotatef( angle , v.getX() , v.getY() , v.getZ() );
}

void Juan::rotate( Vector rot ){
  Juan::rotateX( rot.getX() );
  Juan::rotateY( rot.getY() );
  Juan::rotateZ( rot.getZ() );
}

void Juan::rotateX( float angle ){
  Juan::rotate( angle , Vector(1.0f , 0.0f , 0.0f) );
}

void Juan::rotateY( float angle ){
  Juan::rotate( angle , Vector(0.0f , 1.0f , 0.0f) );
}

void Juan::rotateZ( float angle ){
  Juan::rotate( angle , Vector(0.0f , 0.0f , 1.0f) );
}

void Juan::setCamera( Vector eye , Vector center , Vector up ){
  glMatrixMode( GL_MODELVIEW );
  glLoadIdentity();
  gluLookAt( eye.getX() , eye.getY() , eye.getZ() ,
             center.getX(), center.getY() , center.getZ() ,
             up.getX() , up.getY() , up.getZ() );
}

void Juan::drawLine( Vector start , Vector end ){
  glBegin( GL_LINES );
  glVertex3f( start.getX() , start.getY() , start.getZ() );
  glVertex3f( end.getX() , end.getY() , end.getZ() );
  glEnd();
}

void Juan::drawSolidSphere( float radius , Vector center ){
  glPushMatrix();
  Juan::translate( center );
  glutSolidSphere( radius , 10 , 10);
  glPopMatrix();
}

void Juan::drawSolidCylinder( float radius , Vector start , Vector end , bool closed){
  Juan::drawSolidCylinder( radius , radius , start , end , closed );
}

void Juan::drawSolidCylinder( float srad , float erad , Vector start , Vector end , bool closed){

  Vector dir = end.vectorSub(start);
  Vector z(0,0,1);
  Vector rAxis = z.cross(dir);
  float height = dir.magnitude();
  float angle = 180.0 / 3.14159 * atan( rAxis.magnitude()/z.dot(dir) ) ;

  if( rAxis.magnitude() == 0.0 && angle == 0){
    Vector nDir = dir.normalize();
    Vector addDirZ = nDir.add(z);
    if( addDirZ.magnitude() == 0 ){
      rAxis = Vector(0,1,0);
      angle = 180;
    }
  }

  glPushMatrix();

  Juan::translate( start );
  Juan::rotate( angle , rAxis );

  GLUquadricObj *c = gluNewQuadric();
  gluQuadricDrawStyle (c, GLU_FILL);
  gluCylinder (c, srad, erad, height, 10, 10);

  if( closed ){
    if( srad != 0 ){
      gluQuadricOrientation(c,GLU_OUTSIDE);
      gluDisk( c, 0.0, srad, 10, 10);
    }
    Juan::translate( Vector(0,0,height) );
    if( erad != 0 ){
      gluQuadricOrientation(c,GLU_INSIDE);
      gluDisk( c, 0.0, erad, 10, 10);
    }
  }

  glPopMatrix();

}

void Juan::drawSolidCone( float radius , Vector start , Vector end , bool closed){
  Juan::drawSolidCylinder( radius , 0 , start , end , closed );
}

void Juan::drawSolidIcosahedron( Vector scale , Vector translation , Vector rotation){
  glPushMatrix();

  Juan::translate( translation );
  Juan::rotate( rotation );
  Juan::scale( scale );
  glutSolidOctahedron();

  glPopMatrix();
}

void Juan::drawSegment( Vector start , Vector end , bool inclusive ){

  glColor3f( 0.5 , 0.5 , 0.5 );
  Juan::drawSolidCylinder( Juan::RADIUS , start , end , false );

  glColor3f(0.3,0.3,0.7);
  Juan::drawSolidSphere( Juan::RADIUS , start );

  if( inclusive ){
    Juan::drawSolidSphere( Juan::RADIUS , end );
  }

}

void Juan::drawStage(){

  float xRight = 80;
  float xLeft = -80;
  float yUp = 70;
  float yDown = 1;
  float zFar = 160;
  float zNear = -60;
  float xMidRight = 10;
  float xMidLeft = -10;
  float radius = 4;

  //Floor
  glColor3f(1.0,1.0,1.0);
  glBegin(GL_QUADS);
  glVertex3f(xRight,yDown,zFar);
  glVertex3f(xMidRight,yDown,zFar);
  glVertex3f(xMidRight,yDown,zNear);
  glVertex3f(xRight,yDown,zNear);

  glVertex3f(xLeft,yDown,zFar);
  glVertex3f(xMidLeft,yDown,zFar);
  glVertex3f(xMidLeft,yDown,zNear);
  glVertex3f(xLeft,yDown,zNear);

  //Walls
  glColor3f(0.9,0.9,0.9);

  //Back Wall
  glVertex3f(xLeft,yUp,zNear);
  glVertex3f(xRight,yUp,zNear);
  glVertex3f(xRight,yDown,zNear);
  glVertex3f(xLeft,yDown,zNear);

  //Right wall
  glVertex3f(xLeft,yDown,zFar);
  glVertex3f(xLeft,yDown,zNear);
  glVertex3f(xLeft,yUp,zNear);
  glVertex3f(xLeft,yUp,zFar);

  //Front wall
  glVertex3f(xRight,yDown,zFar);
  glVertex3f(xRight,yUp,zFar);
  glVertex3f(xLeft,yUp,zFar);
  glVertex3f(xLeft,yDown,zFar);

  //Left wall
  glVertex3f(xRight,yDown,zFar);
  glVertex3f(xRight,yUp,zFar);
  glVertex3f(xRight,yUp,zNear);
  glVertex3f(xRight,yDown,zNear);

  //Carpet
  glColor3f(1.0,0.0,0.0);
  glVertex3f(xMidRight,yDown,zFar);
  glVertex3f(xMidLeft,yDown,zFar);
  glVertex3f(xMidLeft,yDown,zNear);
  glVertex3f(xMidRight,yDown,zNear);
  glEnd();

  glColor3f( 0.3,0.3,0.3 );
  Juan::drawSolidCylinder(radius, Vector(xLeft,yDown,zNear) , Vector(xLeft,yUp,zNear) );
  Juan::drawSolidCylinder(radius, Vector(xLeft,yDown,zFar) , Vector(xLeft,yUp,zFar) );
  Juan::drawSolidCylinder(radius, Vector(xRight,yDown,zNear) , Vector(xRight,yUp,zNear) );
  Juan::drawSolidCylinder(radius, Vector(xRight,yDown,zFar) , Vector(xRight,yUp,zFar) );

}

//------------- end of Utility-----------//
