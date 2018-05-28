#include "Fae.h"

//------------- Fae the Fair ------------//
FaeTheFair::FaeTheFair(){}

FaeTheFair::FaeTheFair( float ratio ){
  this->currentFrame = 0;
  this->moving = false;
  this->angle = 0.0f;
  this->ratio = ratio;
  this->loop = false;
  this->frameRate = 1000/30;
  this->setting = 1;
  this->debug = false;
}

FaeTheFair::FaeTheFair( config::SimConfig config ){
  this->currentFrame = config.currentFrame;
  this->moving = config.moving;
  this->angle = config.angle;
  this->ratio = config.ratio;
  this->loop = config.loop;
  this->frameRate = config.frameRate;
  this->setting = config.setting;
  this->debug = config.debug;
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
  this->currentFrame = 0;
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

int FaeTheFair::getTagIndex( Tag name ){
  switch (name) {
    case Tag::SACR : return 0;
    case Tag::LASI : return 1;
    case Tag::LTHI : return 2;
    case Tag::LKNE : return 3;
    case Tag::LTIB : return 4;
    case Tag::LANK : return 5;
    case Tag::LTOE : return 6;
    case Tag::RASI : return 7;
    case Tag::RTHI : return 8;
    case Tag::RKNE : return 9;
    case Tag::RTIB : return 10;
    case Tag::RANK : return 11;
    case Tag::RTOE : return 12;
    default : throw std::logic_error("Tag does not exist.");
  }
}

void FaeTheFair::nextFrame(){
  this->currentFrame++;
  if( this->currentFrame < this->script.size() ){
    this->move( this->script[this->currentFrame] );
  }else{
    if( this->loop ){
      this->currentFrame = -1;
    }else{
      this->moving = false;
    }
  }
}

void FaeTheFair::drawUpperBody(){
  Vector bodyBlue(0.1,0.1,0.5);
  Vector headBrownish(1.0,0.6,0.2);
  Vector simGreen(0.0,1.0,0.0);

  Vector right = this->rasi.vectorSub(this->sacr);
  Vector left  = this->lasi.vectorSub(this->sacr);

  Vector frontDir = right.add(left).normalize();
  Vector baseDir = right.cross(left);
  baseDir = baseDir.normalize();
  Vector relativeRight = frontDir.cross(baseDir);
  Vector relativeLeft  = baseDir.cross(frontDir);

  Vector bodyDir = baseDir.normalize().mult(Juan::RADIUS);
  Vector hipEnd = this->sacr.add(bodyDir).add(baseDir.mult(100));
  Juan::setMaterialDiffuse( bodyBlue );
  Juan::drawSolidCylinder( Juan::RADIUS , Juan::RADIUS * 5 ,
    this->sacr.add(bodyDir) , hipEnd,
    false
  );
  Vector torsoEnd = hipEnd.add( baseDir.mult(500) ) ;
  Juan::drawSolidCylinder(
    Juan::RADIUS * 5 , Juan::RADIUS * 6,
    hipEnd , torsoEnd, false
  );

  Vector neckEnd = torsoEnd.add( baseDir.mult(100) );
  Juan::drawSolidCone(
    Juan::RADIUS * 6 , torsoEnd , neckEnd
  );

  Vector headCenter = neckEnd.add(baseDir.mult(Juan::RADIUS * 2.3));
  Juan::setMaterialDiffuse(headBrownish);
  Juan::drawSolidSphere( Juan::RADIUS*3, headCenter);

  Vector octCenter = headCenter.add( baseDir.mult(Juan::RADIUS*6) );
  Vector octDims(Juan::RADIUS*2,Juan::RADIUS,Juan::RADIUS);
  Vector octRot(0,90,0);
  Juan::setMaterialDiffuse( simGreen );
  Juan::setMaterialSpecular( simGreen );
  Juan::setMaterialAmbient( simGreen );
  Juan::drawSolidOctahedron( octDims , octCenter , octRot );
  Juan::setMaterialAmbient();
  Juan::setMaterialSpecular();

  Vector leftShoulder  = torsoEnd.add(relativeLeft.mult(Juan::RADIUS*6));
  Vector rightShoulder = torsoEnd.add(relativeRight.mult(Juan::RADIUS*6));

  Vector down = baseDir.mult(-1);
  Vector back = frontDir.mult(-1);

  Vector leftElbow = leftShoulder
        .add( down.mult(260) )
        .add( relativeLeft.mult(80) )
        .add( back.mult(80) );
  Vector leftHand = leftElbow
        .add( down.mult(250) )
        .add( frontDir.mult(100) );

  Vector rightElbow = rightShoulder
        .add( down.mult(260) )
        .add( relativeRight.mult(80) )
        .add( back.mult(80) );
  Vector rightHand = rightElbow
        .add( down.mult(250) )
        .add( frontDir.mult(100) );

  Juan::drawSegment( leftShoulder , leftElbow );
  Juan::drawSegment( leftElbow , leftHand , true );

  Juan::drawSegment( rightShoulder , rightElbow );
  Juan::drawSegment( rightElbow , rightHand , true );
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

  this->drawStage();

  if( this->debug ){
    this->drawAxis();
  }
}

void FaeTheFair::drawStage(){
  Vector carpetRed(1,0.0,0.0);

  Position first = this->script[0];
  Position last  = this->script[this->script.size()-1];

  Vector iLeft  = first[getTagIndex(Tag::LTOE)];
  Vector iRight = first[getTagIndex(Tag::RTOE)];

  Vector lLeft  = last[getTagIndex(Tag::LTOE)];
  Vector lRight = last[getTagIndex(Tag::RTOE)];

  Vector a = lLeft.vectorSub( iLeft );
  Vector b = iRight.vectorSub( iLeft );
  Vector planeNorm = a.cross( b ).normalize().mult(Juan::RADIUS*Juan::JOINT_RATIO);

  iLeft = iLeft.add(planeNorm);
  lLeft = lLeft.add(planeNorm);
  iRight = iRight.add(planeNorm);
  lRight = lRight.add(planeNorm);

  Vector leftDir = lLeft.vectorSub(iLeft).normalize();
  iLeft = iLeft.add( leftDir.mult(-500) );
  lLeft = lLeft.add( leftDir.mult(500) );
  Vector rightDir  = lRight.vectorSub(iRight).normalize();
  Vector backDir = iLeft.vectorSub(iRight);
  Vector frontDir = lLeft.vectorSub(lRight);



  float dotprod = backDir.dot( rightDir );
  Vector rightT = rightDir.mult(dotprod);
  iRight = iRight.add(rightT);

  dotprod = frontDir.dot( rightDir );
  rightT = rightDir.mult(dotprod);

  lRight = lRight.add( rightT );

  backDir = iLeft.vectorSub(iRight).normalize();
  frontDir = lLeft.vectorSub(lRight).normalize();

  iRight = iRight.add(backDir.mult(-100));
  iLeft = iLeft.add(backDir.mult(100));

  lRight = lRight.add(frontDir.mult(-100));
  lLeft = lLeft.add(frontDir.mult(100));

  Juan::setMaterialDiffuse( Vector(1,0,0) , 1.0f , GL_FRONT_AND_BACK);
  Juan::setMaterialAmbient( carpetRed , GL_FRONT_AND_BACK);
  //Juan::setMaterialSpecular( carpetRed , GL_FRONT_AND_BACK);
  glBegin(GL_TRIANGLES);
    Juan::vertex( iLeft );
    Juan::vertex( iRight );
    Juan::vertex( lRight );

    Juan::vertex( iLeft );
    Juan::vertex( lLeft );
    Juan::vertex( lRight );
  glEnd();
  Juan::setMaterialAmbient();
  //Juan::setMaterialSpecular();
}

void FaeTheFair::drawAxis(){
  Vector i(300,0,0);
  Vector j(0,300,0);
  Vector k(0,0,300);
  glColor3f(1,0,0);
  Juan::drawLine(this->sacr, this->sacr.add(i));
  glColor3f(0,1,0);
  Juan::drawLine(this->sacr, this->sacr.add(j));
  glColor3f(0,0,1);
  Juan::drawLine(this->sacr, this->sacr.add(k));
}

bool FaeTheFair::isMoving(){
  return this->moving;
}

bool FaeTheFair::toggleMovement(){
  this->moving = !this->moving;
}

void FaeTheFair::restart(){
  this->currentFrame = 0;
  this->move( this->script[this->currentFrame] );
}

bool FaeTheFair::hasEnded(){
  return !(this->currentFrame < this->script.size());
}

float FaeTheFair::getTimeout(){
  return this->frameRate;
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
      std::cout << this->getPosFromIndex(i) << ": "
      << preScript[i].size() << std::endl;
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

void FaeTheFair::toggleLoop(){
  this->loop = !this->loop;
}

void FaeTheFair::cycleFrameRate(){
  this->setting++;
  this->setting = this->setting % 3;
  int p = 1;
  for( int i = 0 ; i < this->setting ; i++){ p *= 2; }
  this->frameRate = 1000/(15 * p);
}

//------------- End Fae      -----------//
