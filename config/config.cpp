#include "config.h"

config::CameraConfig config::getCameraConfig(){
  config::CameraConfig cfig;
  cfig.relativeEye = Vector(0,0,0);
  cfig.center = Vector(0,0,-5.0);
  cfig.up = Vector(0,1,0);
  cfig.rotation = Vector(-90,0,0);
  cfig.defaultRotation = Vector(-90,0,0);
  cfig.pan = Vector(0,0,0);
  cfig.defaultPan = Vector(0,0,0);
  cfig.angle = 5.0f;
  cfig.panning = 30.0f;
  cfig.debug = false;
  return cfig;
}

config::CameraConfig config::getJuanCameraConfig(){
  config::CameraConfig cfig;
  cfig.relativeEye = Vector(0,0,0);
  cfig.center = Vector(0,0,-5.0);
  cfig.up = Vector(0,1,0);
  cfig.rotation = Vector(-90,0,0);
  cfig.defaultRotation = Vector(-90,0,0);
  cfig.pan = Vector(0,0,0);
  cfig.defaultPan = Vector(0,0,0);
  cfig.angle = 5.0f;
  cfig.panning = 30.0f;
  cfig.debug = true;
  return cfig;
}

config::SimConfig config::getSimConfig(){
  SimConfig sfig;
  sfig.filePath = "./res/inputFile.in";
  sfig.currentFrame = 0;
  sfig.moving = false;
  sfig.angle = 0.0f;
  sfig.ratio = 1.0f;
  sfig.loop = false;
  sfig.frameRate = 1000/30;
  sfig.setting = 1;
  sfig.debug = false;
  return sfig;
}

config::SimConfig config::getJuanSimConfig(){
  SimConfig sfig;
  sfig.filePath = "./res/inputFile.in";
  sfig.currentFrame = 0;
  sfig.moving = true;
  sfig.angle = 0.0f;
  sfig.ratio = 1.0f;
  sfig.loop = true;
  sfig.frameRate = 1000/60;
  sfig.setting = 2;
  sfig.debug = true;
  return sfig;
}
