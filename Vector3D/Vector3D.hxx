template <class T>
Vector3D<T>::Vector3D(){}

template <class T>
Vector3D<T>::Vector3D( T x , T y , T z ){
  this->x = x;
  this->y = y;
  this->z = z;
}

template <class T>
Vector3D<T>::~Vector3D<T>(){}

template <class T>
T Vector3D<T>::getX(){ return this->x; }
template <class T>
T Vector3D<T>::getY(){ return this->y; }
template <class T>
T Vector3D<T>::getZ(){ return this->z; }

template <class T>
void Vector3D<T>::setX( T x ){ this->x = x; }
template <class T>
void Vector3D<T>::setY( T y ){ this->y = y; }
template <class T>
void Vector3D<T>::setZ( T z ){ this->z = z; }

template <class T>
Vector3D<T> Vector3D<T>::vectorSub( Vector3D<T> b){
  return Vector3D<T>( this->x - b.getX() , this->y - b.getY() , this->z - b.getZ() );
}

template <class T>
T Vector3D<T>::magnitude(){
  return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

template <class T>
T Vector3D<T>::dot( Vector3D<T> b ){
  return double(this->x*b.x + this->y*b.y + this->z*b.z);
}

template <class T>
Vector3D<T> Vector3D<T>::cross( Vector3D<T> b ){
  T x = (this->y * b.getZ()) - (this->z * b.getY());
  T y = (this->z * b.getX()) - (this->x * b.getZ());
  T z = (this->x * b.getY()) - (this->y * b.getX());
  return Vector3D<T>(x,y,z);
}

template <class T>
Vector3D<T> Vector3D<T>::normalize(){
  float mag = this->magnitude();
  return Vector3D<T>(this->x/mag , this->y/mag, this->z/mag);
}

template <class T>
Vector3D<T> Vector3D<T>::add( Vector3D<T> b){
  return Vector3D<T>( this->x + b.getX() , this->y + b.getY() , this->z + b.getZ() );
}

template <class T>
Vector3D<T> Vector3D<T>::mult(float n){
  return Vector3D<T>( this->x * n , this->y * n , this->z * n );
}

template <class T>
Vector3D<T> Vector3D<T>::mult(Vector3D<T> b){
  return Vector3D<T>(this->x * b.getX() , this->y * b.getY() , this->z * b.getZ());
}

template <class T>
Vector3D<T> Vector3D<T>::rotate( Vector3D<T> rot ){
  Vector3D<T> rota;
  rota = this->rotateX( rot.getX() );
  rota =  rota.rotateY( rot.getY() );
  rota =  rota.rotateZ( rot.getZ() );
  return rota;
}

template <class T>
Vector3D<T> Vector3D<T>::rotateX(float angle){
  float radians = Vector3D<T>::toRadians(angle);
  Vector3D<T> rot;
  rot.setX( this->x );
  rot.setY( this->y*cos(radians) - this->z*sin(radians) );
  rot.setZ( this->y*sin(radians) + this->z*cos(radians) );
  return rot;
}

template <class T>
Vector3D<T> Vector3D<T>::rotateY(float angle){
  float radians = Vector3D<T>::toRadians(angle);
  Vector3D<T> rot;
  rot.setX(  this->x*cos(radians) + this->z*sin(radians) );
  rot.setY( this->y );
  rot.setZ( -(this->x)*sin(radians) + this->z*cos(radians) );
  return rot;
}

template <class T>
Vector3D<T> Vector3D<T>::rotateZ(float angle){
  float radians = Vector3D<T>::toRadians(angle);
  Vector3D<T> rot;
  rot.setX( x*cos(radians) - y*sin(radians) );
  rot.setY( x*sin(radians) + y*cos(radians) );
  rot.setZ( this->z );
  return rot;
}


template <class T>
std::string Vector3D<T>::toString(){
  std::stringstream ss;
  ss << this->x << " " << this->y << " " << this->z;
  std::string xs, ys, zs;
  ss >> xs >> ys >> zs;
  return "[" + xs + " , " + ys + " , " + zs + "]";
}

template <class T>
bool Vector3D<T>::equals( Vector3D<T> v ){
  return this->x == v.x && this->y == v.y && this->z == v.z;
}

template <class T>
T* Vector3D<T>::toArray(){
  T* e = new T[3];
  e[0] = this->x;
  e[1] = this->y;
  e[2] = this->z;
  return e;
}

template <class T>
float Vector3D<T>::toRadians(float degrees){
  return degrees * M_PI / 180;
}

template <class T>
float Vector3D<T>::toDegrees(float radians){
  return radians * 180 / M_PI;
}
