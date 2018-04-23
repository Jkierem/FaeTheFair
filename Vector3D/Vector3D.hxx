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
float Vector3D<T>::magnitude(){
  return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

template <class T>
T Vector3D<T>::dot( Vector3D<T> b ){
  return this->x*b.getX() + this->y*b.getY() + this->z*b.getZ();
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
std::string Vector3D<T>::toString(){
  std::stringstream ss;
  ss << this->x << " " << this->y << " " << this->z;
  std::string xs, ys, zs;
  ss >> xs >> ys >> zs;
  return "[" + xs + " , " + ys + " , " + zs + "]";
}

template <class T>
Vector3D<T> Vector3D<T>::mult(float n){
  return Vector3D<T>( this->x * n , this->y * n , this->z * n );
}
template <class T>
Vector3D<T> Vector3D<T>::mult(Vector3D<T> b){
  return Vector3D<T>(this->x * b.getX() , this->y * b.getY() , this->z * b.getZ());
}
