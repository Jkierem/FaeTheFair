#ifndef __CONFIG__H__
#define __CONFIG__H__

#include <string>
#include "../Vector3D/Vector3D.h"

namespace config {
  struct CameraConfig{
    Vector relativeEye;
    Vector center;
    Vector up;
    Vector rotation;
    Vector defaultRotation;
    Vector pan;
    Vector defaultPan;
    float angle;
    float panning;
    bool debug;
  };

  struct SimConfig{
    std::string filePath;
    int currentFrame;
    bool moving;
    float angle;
    float ratio;
    bool loop;
    float frameRate;
    int setting;
    bool debug;
    bool inputDebug;
  };

  CameraConfig getCameraConfig();
  CameraConfig getJuanCameraConfig();
  SimConfig getSimConfig();
  SimConfig getJuanSimConfig();

} /* config */

#endif
