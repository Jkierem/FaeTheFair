#ifndef __CAMERA_HANDLER__H__
#define __CAMERA_HANDLER__H__

#include "../Juan/Juan.h"
#include "../Vector3D/Vector3D.h"

class CameraHandler {
private:

  Vector relativeEye;
  Vector center;
  Vector up;
  Vector rotation;
  Vector defaultPan;
  Vector pan;
  Vector defaultRot;
  float angle;
  float panning;

public:
  CameraHandler ();
  CameraHandler ( Vector defaultRot );
  CameraHandler ( Vector defaultRot , Vector defaultPan );
  virtual ~CameraHandler ();

  void setRelativeEye( Vector eye );
  void lookAt( Vector center );
  void setUp( Vector up );
  void move( Vector to );
  void update();

  void panUp();
  void panDown();
  void panLeft();
  void panRight();
  void panNear();
  void panFar();

  void rotateXPositive();
  void rotateXNegative();
  void rotateYPositive();
  void rotateYNegative();
  void rotateZPositive();
  void rotateZNegative();

  void rotateX(float angle);
  void rotateY(float angle);
  void rotateZ(float angle);

  void resetRotation();
  void resetPanning();
  void setCurrentRotationAsDefault();
  void setCurrentPanningAsDefault();
};

typedef CameraHandler Camera;

#endif
