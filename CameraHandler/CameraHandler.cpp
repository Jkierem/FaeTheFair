#include "CameraHandler.h"

CameraHandler::CameraHandler (){
  this->relativeEye = Vector(0,0,0);
  this->center = Vector(0,0,-5.0);
  this->up = Vector(0,1,0);
  this->rotation = Vector(0,0,0);
  this->defaultRot = Vector(0,0,0);
  this->pan = Vector(0,0,0);
  this->defaultPan = Vector(0,0,0);
  this->angle = 5.0f;
  this->panning = 30.0f;
}

CameraHandler::CameraHandler ( Vector defaultRot ){
  this->relativeEye = Vector(0,0,0);
  this->center = Vector(0,0,-5.0);
  this->up = Vector(0,1,0);
  this->rotation = defaultRot;
  this->defaultRot = defaultRot;
  this->pan = Vector(0,0,0);
  this->defaultPan = Vector(0,0,0);
  this->angle = 5.0f;
  this->panning = 30.0f;
  this->debug = false;
}

CameraHandler::CameraHandler ( Vector defaultRot , Vector defaultPan ){
  this->relativeEye = Vector(0,0,0);
  this->center = Vector(0,0,-5.0);
  this->up = Vector(0,1,0);
  this->rotation = defaultRot;
  this->defaultRot = defaultRot;
  this->pan = defaultPan;
  this->defaultPan = defaultPan;
  this->angle = 5.0f;
  this->panning = 30.0f;
  this->debug = false;
}

CameraHandler::CameraHandler ( config::CameraConfig config ){
  this->relativeEye = config.relativeEye;
  this->center = config.center;
  this->up = config.up;
  this->rotation = config.rotation;
  this->defaultRot = config.defaultRotation;
  this->pan = config.pan;
  this->defaultPan = config.defaultPan;
  this->angle = config.angle;
  this->panning = config.panning;
  this->debug = config.debug;
}

CameraHandler::~CameraHandler (){}

void CameraHandler::setRelativeEye( Vector eye ){
  this->relativeEye = eye;
}

void CameraHandler::lookAt( Vector center ){
  this->center = center;
}

void CameraHandler::setUp( Vector up ){
  this->up = up;
}

void CameraHandler::move( Vector to ){
  this->relativeEye = this->relativeEye.add(to);
}

void CameraHandler::update(){
  Juan::setCamera( this->center.add(this->relativeEye) , this->center , this->up );
  Juan::translate(this->center);
  Juan::rotate(this->rotation);
  Juan::translate(this->center.mult(-1));
  Juan::translate(this->pan);
  if( this->debug ){
    this->drawPanning();
  }
}

void CameraHandler::panUp(){
  this->pan = this->pan.add(Vector(0,this->panning*-1,0));
}
void CameraHandler::panDown(){
  this->pan = this->pan.add(Vector(0,this->panning,0));
}
void CameraHandler::panLeft(){
  this->pan = this->pan.add(Vector(this->panning,0,0));
}
void CameraHandler::panRight(){
  this->pan = this->pan.add(Vector(this->panning*-1,0,0));
}
void CameraHandler::panNear(){
  this->pan = this->pan.add(Vector(0,0,this->panning*-1));
}
void CameraHandler::panFar(){
  this->pan = this->pan.add(Vector(0,0,this->panning));
}

void CameraHandler::rotateXPositive(){
  this->rotation = this->rotation.add(Vector(this->angle,0,0));
}
void CameraHandler::rotateXNegative(){
  this->rotation = this->rotation.add(Vector(this->angle*-1,0,0));
}
void CameraHandler::rotateYPositive(){
  this->rotation = this->rotation.add(Vector(0,this->angle,0));
}
void CameraHandler::rotateYNegative(){
  this->rotation = this->rotation.add(Vector(0,this->angle*-1,0));
}
void CameraHandler::rotateZPositive(){
  this->rotation = this->rotation.add(Vector(0,0,this->angle));
}
void CameraHandler::rotateZNegative(){
  this->rotation = this->rotation.add(Vector(0,0,this->angle*-1));
}

void CameraHandler::rotateX(float angle){
  this->rotation = this->rotation.add(Vector(angle,0,0));
}

void CameraHandler::rotateY(float angle){
  this->rotation = this->rotation.add(Vector(0,angle,0));
}

void CameraHandler::rotateZ(float angle){
  this->rotation = this->rotation.add(Vector(0,0,angle));
}

void CameraHandler::resetRotation(){
  this->rotation = this->defaultRot;
}

void CameraHandler::resetPanning(){
  this->pan = this->defaultPan;
}

void CameraHandler::setCurrentRotationAsDefault(){
  this->defaultRot = this->rotation;
}

void CameraHandler::setCurrentPanningAsDefault(){
  this->defaultPan = this->pan;
}

void CameraHandler::drawPanning(){
  Vector o = this->center.add(Vector(-300,-300,-300));
  Vector i(this->pan.getX(),0,0);
  Vector j(0,this->pan.getY(),0);
  Vector k(0,0,this->pan.getZ());
  glColor3f(1,0,1);
  Juan::drawLine(o, o.add(this->pan) );
  glColor3f(1,0,0);
  Juan::drawLine(o, o.add(i) );
  glColor3f(0,1,0);
  Juan::drawLine(o, o.add(j) );
  glColor3f(0,0,1);
  Juan::drawLine(o, o.add(k) );
}
