#include "LightHandler.h"

bool Utils::Light::equals( Utils::Light l ){
  return (
    this->pos.equals(l.pos) &&
    this->color_ambient.equals(l.color_ambient) &&
    this->color_diffuse.equals(l.color_diffuse) &&
    this->color_spec.equals(l.color_spec) &&
    this->alphas.equals(l.alphas) &&
    this->mappedLight == l.mappedLight &&
    this->type == l.type &&
    this->enabled == l.enabled
  );
}

GLenum LightHandler::getLightMapping( int light ){
  switch (light) {
    case 0:
      return GL_LIGHT0;
    break;
    case 1:
      return GL_LIGHT1;
    break;
    case 2:
      return GL_LIGHT2;
    break;
    case 3:
      return GL_LIGHT3;
    break;
    case 4:
      return GL_LIGHT4;
    break;
    case 5:
      return GL_LIGHT5;
    break;
    case 6:
      return GL_LIGHT6;
    break;
    case 7:
      return GL_LIGHT7;
    break;
    default:
      throw std::logic_error("Error: Light range is between 0-7.");
    break;
  }
}

Utils::Light LightHandler::createLight( int i ){
  Utils::Light l;
  l.pos = Vector();
  l.color_ambient = Vector();
  l.color_diffuse = Vector(1,1,1);
  l.color_spec = Vector(1,1,1);
  l.alphas = Vector(1,1,1);
  l.mappedLight = getLightMapping(i);
  l.type = DISTANTE;
  return l;
}

Utils::Light LightHandler::createLight(){
  Utils::Light l;
  l.pos = Vector();
  l.color_ambient = Vector();
  l.color_diffuse = Vector(1,1,1);
  l.color_spec = Vector(1,1,1);
  l.alphas = Vector(1,1,1);
  l.mappedLight = GL_LIGHT0;
  l.type = DISTANTE;
  return l;
}

LightHandler::LightHandler(){
  this->enabled = false;
  for (int i = 0; i < 8; i++) {
    Utils::Light l = this->createLight(i);
    this->lights.push_back( l );
    this->prev_lights.push_back( l );
  }
}

LightHandler::~LightHandler(){}

Vector LightHandler::getPos( int light ){
  return this->lights[light].pos;
}

Vector LightHandler::getAmbientColor( int light ){
  return this->lights[light].color_ambient;
}

Vector LightHandler::getDiffuseColor( int light ){
  return this->lights[light].color_diffuse;
}

Vector LightHandler::getSpecColor( int light ){
  return this->lights[light].color_spec;
}


void LightHandler::setPos( int light , Vector pos ){
  this->lights[light].pos = pos;
}

void LightHandler::setAmbientColor( int light , Vector color , float alpha ){
  this->lights[light].color_ambient = color;
  this->lights[light].alphas.setX(alpha);
}

void LightHandler::setDiffuseColor( int light , Vector color , float alpha ){
  this->lights[light].color_diffuse = color;
  this->lights[light].alphas.setY(alpha);
}

void LightHandler::setSpecColor( int light , Vector color , float alpha ){
  this->lights[light].color_spec = color;
  this->lights[light].alphas.setZ(alpha);
}


void LightHandler::enableLighting(){
  glEnable(GL_LIGHTING);
  this->enabled = true;
}

void LightHandler::disableLighting(){
  glDisable(GL_LIGHTING);
  this->enabled = false;
}

void LightHandler::toggleLight( int light ){
  this->lights[light].enabled = !this->lights[light].enabled;
}

void LightHandler::enableLight( int light ){
  this->lights[light].enabled = true;
}

void LightHandler::disableLight( int light ){
  this->lights[light].enabled = false;
}

void LightHandler::updateLight( Utils::Light *curr , Utils::Light *prev ){
  //do the opengl stuff here
  if( !prev->pos.equals( curr->pos ) ){
    prev->pos = curr->pos;
    float type = curr->type == DISTANTE ? 0 : 1 ;
    Juan::setLightPosition( curr->mappedLight , curr->pos , type );
  }
  if( !prev->color_ambient.equals( curr->color_ambient ) ){
    prev->color_ambient = curr->color_ambient;
    Juan::setLightAmbient( curr->mappedLight , curr->color_ambient , curr->alphas.getX() );
  }
  if( !prev->color_diffuse.equals( curr->color_diffuse ) ){
    prev->color_diffuse = curr->color_diffuse;
    Juan::setLightDiffuse( curr->mappedLight , curr->color_diffuse , curr->alphas.getY() );
  }
  if( !prev->color_spec.equals( curr->color_spec ) ){
    prev->color_spec = curr->color_spec;
    Juan::setLightSpecular( curr->mappedLight , curr->color_spec , curr->alphas.getZ() );
  }
  if( prev->enabled != curr->enabled ){
    prev->enabled = curr->enabled;
    if( curr->enabled ){
      glEnable(curr->mappedLight);
    }else{
      glDisable(curr->mappedLight);
    }
  }
  if( prev->type != curr->type ){
    prev->type = curr->type;
    float type = curr->type == DISTANTE ? 0 : 1 ;
    Juan::setLightPosition( curr->mappedLight , curr->pos , type );
  }
}

void LightHandler::refresh(){
  if( this->enabled ){
    for ( int i = 0 ; i < 8 ; i++ ){
      Utils::Light *l = &(this->lights[i]);
      Utils::Light *pl = &(this->prev_lights[i]);
      if( !l->equals(*pl) ){
        updateLight( l , pl );
      }
    }
  }
}
