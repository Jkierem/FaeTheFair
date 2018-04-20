#include "Fae.h"

//------------- Fae the Fair ------------//

FaeTheFair::FaeTheFair( float ratio ){
  this->currentFrame = 0;
  this->moving = false;
  this->angle = 0.0f;
  this->ratio = ratio;
}

FaeTheFair::~FaeTheFair (){}

void FaeTheFair::setRatio( float ratio ){
  this->ratio = ratio;
}

void FaeTheFair::readScript( std::string filePath ){
  MovementScript script;
  Position p;

  MovementScript values( 13 , Position() );
  int current = -1;

  std::ifstream infile(filePath);
  std::string line;
  while( std::getline(infile , line) && current < 13 ){
    if( std::isdigit(line[0]) || line[0] == '-' ){
      std::stringstream ss(line);
      float x,y,z;
      ss >> x >> y >> z;
      Vector v = Vector(x,y,z);
      values[current].push_back(v);
    }else{
      current++;
    }
  }
  if( this->checkPreScript(values) ){
    values = this->fixPreScript(values);
    this->setScript(this->processPreScript(values));
  }else{
    std::string msg("Input file has different number of positions for");
    msg += " each point.\n Check console for Debugging";
    throw std::logic_error(msg);
  }
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
  Vector rot(0,this->angle,0);
  this->angle += this->ratio;
  Juan::drawSolidOctahedron(scale,neckish,rot);

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

bool FaeTheFair::checkPreScript( MovementScript preScript ){
  std::vector<int> errors;
  int size;
  if( preScript.size() != 13 ){
    return false;
  }else{
    size = preScript[0].size();
    for (int i = 1; i < 13; i++) {
      if( preScript[i].size() != size ){
        errors.push_back(i);
      }
    }
  }
  if( errors.size() > 0 ){
    std::cout << "Expected size: " << size << std::endl;
    for (size_t i = 0; i < preScript.size(); i++) {
      std::cout << this->getPosFromIndex(i) << ": " << preScript[i].size() << std::endl;
    }
    return false;
  }
  return true;
}

MovementScript FaeTheFair::processPreScript( MovementScript preScript ){
  MovementScript script;
  int pointsInTime = preScript[0].size();
  for( int i = 0 ; i < pointsInTime ; i++){
    Position aux;
    for( int j = 0 ; j < 13 ; j++ ){
      aux.push_back( preScript[j][i] );
    }
    script.push_back( aux );
  }
  return script;
}

Vector FaeTheFair::getPoint( Tag t ){
  switch (t) {
    case Tag::SACR : return this->sacr;
    case Tag::LASI : return this->lasi;
    case Tag::LTHI : return this->lthi;
    case Tag::LKNE : return this->lkne;
    case Tag::LTIB : return this->ltib;
    case Tag::LANK : return this->lank;
    case Tag::LTOE : return this->ltoe;
    case Tag::RASI : return this->rasi;
    case Tag::RTHI : return this->rthi;
    case Tag::RKNE : return this->rkne;
    case Tag::RTIB : return this->rtib;
    case Tag::RANK : return this->rank;
    case Tag::RTOE : return this->rtoe;
    default : throw std::logic_error("Tag does not exist.");
  }
}

MovementScript FaeTheFair::fixPreScript( MovementScript preScript ){
  MovementScript fixed;
  for (int i = 0; i < preScript.size(); i++) {
    Position current = preScript[i];
    Position np;
    for (int j = 0; j < current.size(); j++) {
      Vector cv = current[j];
      if( cv.magnitude() == 0 ){
        cv = np[j-1];
      }
      np.push_back(cv);
    }
    fixed.push_back(np);
  }
  return fixed;
}

void FaeTheFair::checkFixedPreScript( MovementScript preScript ){
  bool fixed = true;
  for (int i = 0; i < preScript.size(); i++) {
    Position current = preScript[i];
    int ceros = 0;
    for (int j = 0; j < current.size() ; j++) {
      if( current[j].magnitude() == 0 ){
        ceros++;
      }
    }
    if( ceros ){
      fixed = false;
    }
    std::cout << this->getPosFromIndex(i) << ": " << ceros << std::endl;
  }
  std::string sf = fixed? "TRUE" : "FALSE";
  std::cout << "Fixed: " << sf << std::endl;
}

void FaeTheFair::printScript(){
  for ( int  i = 0 ; i < this->script.size() ; i++ ){
    std::cout << "Posicion " << i << std::endl;
    for( int j = 0 ; j < this->script[i].size() ; j++ ){
      std::cout << "\t" << this->getPosFromIndex(j) << ":";
      std::cout << this->script[i][j].toString() << std::endl;
    }
    std::cout << std::endl;
  }
}

std::string FaeTheFair::getPosFromIndex(int i){
  switch (static_cast<Tag>(i)) {
    case Tag::SACR : return "SACR";
    case Tag::LASI : return "LASI";
    case Tag::LTHI : return "LTHI";
    case Tag::LKNE : return "LKNE";
    case Tag::LTIB : return "LTIB";
    case Tag::LANK : return "LANK";
    case Tag::LTOE : return "LTOE";
    case Tag::RASI : return "RASI";
    case Tag::RTHI : return "RTHI";
    case Tag::RKNE : return "RKNE";
    case Tag::RTIB : return "RTIB";
    case Tag::RANK : return "RANK";
    case Tag::RTOE : return "RTOE";
    default : return "UNKOWN";
  }
}

//------------- End Fae      -----------//
