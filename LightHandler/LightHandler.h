#ifndef __LIGHT__H__
#define __LIGHT__H__

#include <GL/glut.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <vector> //std::vector class
#include <stdexcept> //std::logic_error

#include "../Juan/Juan.h"
#include "../Vector3D/Vector3D.h"

enum LType { DISTANTE=0, PUNTUAL=1 };

namespace Utils {
  struct Light {
    Vector pos;
    Vector color_ambient;
    Vector color_diffuse;
    Vector color_spec;
    Vector alphas;
    GLenum mappedLight;
    LType type;
    bool enabled;
    bool equals( Utils::Light l );
  };
} /* Utils */

class LightHandler{
protected:
  std::vector<Utils::Light> lights;
  std::vector<Utils::Light> prev_lights;
  bool enabled;

  GLenum getLightMapping( int light );
  Utils::Light createLight( int i );
  Utils::Light createLight();

public:
  LightHandler();
  virtual ~LightHandler();

  Vector getPos( int light );
  Vector getAmbientColor( int light );
  Vector getDiffuseColor( int light );
  Vector getSpecColor( int light );

  void setPos( int light , Vector pos );
  void setAmbientColor( int light , Vector color , float alpha );
  void setDiffuseColor( int light , Vector color , float alpha );
  void setSpecColor( int light , Vector color , float alpha );

  void enableLighting();
  void disableLighting();

  void toggleLight( int light );
  void enableLight( int light );
  void disableLight( int light );

  void updateLight( Utils::Light *curr , Utils::Light *prev );
  void refresh();

};

typedef LightHandler Light;

#endif
