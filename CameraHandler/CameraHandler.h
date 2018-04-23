#ifndef __CAMERA_HANDLER__H__
#define __CAMERA_HANDLER__H__

#include "../Juan/Juan.h"
#include "../Vector3D/Vector3D.h"

class CameraHandler {
private:

  Vector eye;
  Vector center;
  Vector up;
  Vector rotation;
  Vector defaultRot;
  float angle;

public:
  CameraHandler ();
  CameraHandler ( Vector defaultRot );
  virtual ~CameraHandler ();

  void setPos( Vector eye );
  void lookAt( Vector center );
  void setUp( Vector up );
  void move( Vector to );
  void update();
  Vector getEye();
  Vector getCenter();
  Vector getUp();

  void rotateRight();
  void rotateLeft();
  void rotateUp();
  void rotateDown();

  void rotateX(float angle);
  void rotateY(float angle);
  void rotateZ(float angle);

  void resetRotation();
};

#endif
