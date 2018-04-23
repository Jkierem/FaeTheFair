#include "CameraHandler.h"

CameraHandler::CameraHandler (){
  this->eye = Vector(0,0,0);
  this->center = Vector(0,0,-5.0);
  this->up = Vector(0,1,0);
  this->rotation = Vector(0,0,0);
  this->defaultRot = Vector(0,0,0);
  this->angle = 5.0f;
}

CameraHandler::CameraHandler ( Vector defaultRot ){
  this->eye = Vector(0,0,0);
  this->center = Vector(0,0,-5.0);
  this->up = Vector(0,1,0);
  this->rotation = defaultRot;
  this->defaultRot = defaultRot;
  this->angle = 5.0f;
}

CameraHandler::~CameraHandler (){}

void CameraHandler::setPos( Vector eye ){
  this->eye = eye;
}

void CameraHandler::lookAt( Vector center ){
  this->center = center;
}

void CameraHandler::setUp( Vector up ){
  this->up = up;
}

void CameraHandler::move( Vector to ){
  this->eye = this->eye.add(to);
}

void CameraHandler::update(){
  Juan::setCamera( this->eye , this->center , this->up );
  Juan::rotate(this->rotation);
}

Vector CameraHandler::getEye(){ return this->eye; }
Vector CameraHandler::getCenter(){ return this->center; }
Vector CameraHandler::getUp(){ return this->up; }

void CameraHandler::rotateRight(){
  this->rotation = this->rotation.add(Vector(0,0,this->angle));
}
void CameraHandler::rotateLeft(){
  this->rotation = this->rotation.add(Vector(0,0,this->angle*-1));
}
void CameraHandler::rotateUp(){
  this->rotation = this->rotation.add(Vector(this->angle,0,0));
}
void CameraHandler::rotateDown(){
  this->rotation = this->rotation.add(Vector(this->angle*-1,0,0));
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
