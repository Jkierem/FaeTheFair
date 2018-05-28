#ifndef __JUAN__H__
#define __JUAN__H__

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <vector>

#include <iostream>
#include <cmath>

#include "../Vector3D/Vector3D.h"

namespace Juan {
  const float RADIUS = 50;
  const float JOINT_RATIO = 1.20;
  //mascaras
  void translate( Vector t );

  void scale( Vector s );

  void rotate( float angle , Vector v ); //rotate around vector
  void rotate( Vector rot ); //rotation on each axis
  void rotateX( float angle );//rotation around X
  void rotateY( float angle );//rotation around Y
  void rotateZ( float angle );//rotation around Z

  void vertex( Vector v );

  void setCamera( Vector eye , Vector center , Vector up , bool identity=true);

  //Figures
  void drawLine( Vector start , Vector end );
  void drawSolidSphere( float radius , Vector center );
  void drawSolidCylinder( float radius , Vector start , Vector end , bool closed=true);
  void drawSolidCylinder( float srad , float erad , Vector start , Vector end , bool closed=true);
  void drawSolidCone( float radius , Vector start , Vector end , bool closed=true );
  void drawSolidOctahedron( Vector scale , Vector translation , Vector rotation);

  void drawSegment( Vector start , Vector end , bool inclusive=false );
  void setNormal( Vector normal );

  void setMaterialAmbient( Vector value , GLenum face=GL_FRONT );
  void setMaterialDiffuse( Vector value , float alpha=1.0f , GLenum face=GL_FRONT );
  void setMaterialSpecular( Vector value , GLenum face=GL_FRONT );

  void setLightAmbient( GLenum light , Vector value , float alpha=1.0f);
  void setLightDiffuse( GLenum light , Vector value , float alpha=1.0f);
  void setLightSpecular( GLenum light , Vector value , float alpha=1.0f);

  void setLightPosition( GLenum light , Vector value , float type );

} /* Juan */


#endif
