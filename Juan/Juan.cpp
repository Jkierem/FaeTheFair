#include "Juan.h"

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

void Juan::vertex( Vector v ){
  glVertex3f( v.getX() , v.getY() , v.getZ() );
}

void Juan::setCamera( Vector eye , Vector center , Vector up , bool identity ){
  glMatrixMode( GL_MODELVIEW );
  if(identity){
    glLoadIdentity();
  }
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
  float angle = (180.0 / 3.14159) * (acos( z.dot(dir) / height )) ;

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

void Juan::drawSolidOctahedron( Vector scale , Vector translation , Vector rotation){
  glPushMatrix();

  Juan::translate( translation );
  Juan::rotate( rotation );
  Juan::scale( scale );
  glutSolidOctahedron();

  glPopMatrix();
}

void Juan::drawSegment( Vector start , Vector end , bool inclusive ){

  glColor3f( 0.5 , 0.5 , 0.5 );
  Juan::setMaterialDiffuse( Vector(0.5,0.5,0.5) );
  Juan::drawSolidCylinder( Juan::RADIUS , start , end , false );

  glColor3f(0.3,0.3,0.7);
  Juan::setMaterialDiffuse( Vector(0.3,0.3,0.7) );
  Juan::drawSolidSphere( Juan::RADIUS*Juan::JOINT_RATIO , start );

  if( inclusive ){
    Juan::drawSolidSphere( Juan::RADIUS*Juan::JOINT_RATIO , end );
  }

}

void Juan::setNormal( Vector normal ){
  glNormal3f(normal.getX(),normal.getY(),normal.getZ());
}

void Juan::setMaterialAmbient( Vector value , GLenum face ){
  GLfloat color[4];
  color[0] = value.getX();
  color[1] = value.getY();
  color[2] = value.getZ();
  color[3] = 1.0f;
  glMaterialfv( face , GL_AMBIENT , color );
}

void Juan::setMaterialDiffuse( Vector value , float alpha , GLenum face ){
  GLfloat color[4];
  color[0] = value.getX();
  color[1] = value.getY();
  color[2] = value.getZ();
  color[3] = alpha;
  glMaterialfv( face , GL_DIFFUSE , color );
}

void Juan::setMaterialSpecular( Vector value , GLenum face ){
  GLfloat color[4];
  color[0] = value.getX();
  color[1] = value.getY();
  color[2] = value.getZ();
  color[3] = 1.0f;
  glMaterialfv( face , GL_SPECULAR , color );
}

void Juan::setLightAmbient( GLenum light , Vector value , float alpha ){
  GLfloat color[4];
  color[0] = value.getX();
  color[1] = value.getY();
  color[2] = value.getZ();
  color[3] = alpha;
  glLightfv(light , GL_AMBIENT , color );
}

void Juan::setLightDiffuse( GLenum light , Vector value , float alpha ){
  GLfloat color[4];
  color[0] = value.getX();
  color[1] = value.getY();
  color[2] = value.getZ();
  color[3] = alpha;
  glLightfv(light , GL_DIFFUSE , color );
}

void Juan::setLightSpecular( GLenum light , Vector value , float alpha ){
  GLfloat color[4];
  color[0] = value.getX();
  color[1] = value.getY();
  color[2] = value.getZ();
  color[3] = alpha;
  glLightfv(light , GL_SPECULAR , color );
}


void Juan::setLightPosition( GLenum light , Vector value , float type ){
  GLfloat pos[4];
  pos[0] = value.getX();
  pos[1] = value.getY();
  pos[2] = value.getZ();
  pos[3] = type;
  glLightfv(light , GL_POSITION , pos );
}


//------------- end of Utility-----------//
