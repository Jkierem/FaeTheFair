#include "Fae.h"
#include <stdexcept>

//------------- Fae the Fair ------------//

FaeTheFair::FaeTheFair( ){
  this->currentFrame = 0;
  this->moving = false;
}

FaeTheFair::~FaeTheFair (){}

void FaeTheFair::readScript( std::string filePath ){
  //Placeholder code for later
  //This function shall read the input file later
  //For now it will give us a Placeholder array of positions with one Position
  MovementScript script;
  Position p;

  p.push_back( Vector(0,20,20) ); //sacr

  p.push_back( Vector(-5,19,20) ); //lasi
  p.push_back( Vector(-5,14,20) ); //lthi
  p.push_back( Vector(-5,10,20) ); //lkne
  p.push_back( Vector(-5,10,15) ); //ltib
  p.push_back( Vector(-5,10,11) ); //lank
  p.push_back( Vector(-5,7,11)  ); //ltoe

  p.push_back( Vector(5,19,20) ); //rasi
  p.push_back( Vector(5,16,22) ); //rthi
  p.push_back( Vector(5,12,25) ); //rkne
  p.push_back( Vector(5,8,25)  ); //rtib
  p.push_back( Vector(5,3,25)  ); //rank
  p.push_back( Vector(5,3,28)  ); //rtoe

  script.push_back(p);
  this->setScript(script);
}

void FaeTheFair::setScript( MovementScript script ){
  this->script = script;
  this->move( script[this->currentFrame] );
}

void FaeTheFair::move( Position nextPos ){
  if( nextPos.size() != 13 ){
    throw new std::invalid_argument("Next position is invalid");
  }

  this->sacr = nextPos[0];

  this->lasi = nextPos[1];
  this->lthi = nextPos[2];
  this->lkne = nextPos[3];
  this->ltib = nextPos[4];
  this->lank = nextPos[5];
  this->ltoe = nextPos[6];

  this->rasi = nextPos[7];
  this->rthi = nextPos[8];
  this->rkne = nextPos[9];
  this->rtib = nextPos[10];
  this->rank = nextPos[11];
  this->rtoe = nextPos[12];

}

void FaeTheFair::nextFrame(){
  if( this->currentFrame < this->script.size() ){
    this->currentFrame++;
    this->move( this->script[this->currentFrame] );
  }else{
    this->moving = false;
  }
}

void FaeTheFair::drawUpperBody(){

  glColor3f(0.1,0.1,0.5);
  Vector coneTop( this->sacr.getX() , this->sacr.getY() + 3 , this->sacr.getZ());
  Juan::drawSolidCone( 3, coneTop , this->sacr );
  Vector cTop( coneTop.getX() , coneTop.getY() + 10 , coneTop.getZ() );
  Juan::drawSolidCylinder(3 , 4, coneTop , cTop ) ;

  Vector neckish = Vector( cTop.getX() , cTop.getY() + 2 , cTop.getZ() );
  Juan::drawSolidCone( 4 , cTop, neckish );

  glColor3f(1.0,0.6,0.2);
  neckish.setY( neckish.getY() + 2.5);
  Juan::drawSolidSphere(3, neckish);

  glColor3f(0.0,1.0,0.0);
  Vector scale(1,2,1);
  neckish.setY( neckish.getY() + 6);
  Vector rot(0,0,0);
  Juan::drawSolidIcosahedron(scale,neckish,rot);

  Vector lshoulder( cTop.getX() + 4 , cTop.getY() , cTop.getZ());
  Vector lelbow( lshoulder.getX() + 2 , lshoulder.getY() - 5 , lshoulder.getZ() );
  Juan::drawSegment( lshoulder , lelbow);
  Vector lhand(lelbow.getX() , lelbow.getY() - 3 , lelbow.getZ() + 6);
  Juan::drawSegment(lelbow,lhand,true);

  Vector rshoulder( cTop.getX() - 4 , cTop.getY() , cTop.getZ());
  Vector relbow( rshoulder.getX() -2 , rshoulder.getY() - 5 , rshoulder.getZ() );
  Juan::drawSegment( rshoulder , relbow);
  Vector rhand(relbow.getX() , relbow.getY() - 3 , relbow.getZ() + 6);
  Juan::drawSegment(relbow,rhand,true);
}

void FaeTheFair::draw(){
  this->drawUpperBody();
  //Hip
  Juan::drawSegment( this->sacr , this->lasi );
  Juan::drawSegment( this->sacr , this->rasi );

  //Left leg
  Juan::drawSegment( this->lasi , this->lthi );
  Juan::drawSegment( this->lthi , this->lkne );
  Juan::drawSegment( this->lkne , this->ltib );
  Juan::drawSegment( this->ltib , this->lank );
  Juan::drawSegment( this->lank , this->ltoe , true );

  //Right leg
  Juan::drawSegment( this->rasi , this->rthi );
  Juan::drawSegment( this->rthi , this->rkne );
  Juan::drawSegment( this->rkne , this->rtib );
  Juan::drawSegment( this->rtib , this->rank );
  Juan::drawSegment( this->rank , this->rtoe , true );
}

bool FaeTheFair::isMoving(){
  return this->moving;
}

bool FaeTheFair::toggleMovement(){
  this->moving = !this->moving;
}

void FaeTheFair::restart(){
  this->currentFrame = 0;
}

bool FaeTheFair::hasEnded(){
  return !(this->currentFrame < this->script.size());
}

//------------- End Fae      -----------//
