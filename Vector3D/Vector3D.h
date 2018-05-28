#ifndef __VECTOR3D__H__
#define __VECTOR3D__H__

#include <string>
#include <cmath>
#include <sstream>
#include <vector>

template <class T>
class Vector3D {
protected:
  T x;
  T y;
  T z;
public:
  Vector3D();
  Vector3D ( T x , T y , T z );
  virtual ~Vector3D ();

  T getX();
  T getY();
  T getZ();

  void setX( T x );
  void setY( T y );
  void setZ( T z );

  Vector3D<T> vectorSub( Vector3D<T> b);
  float magnitude();
  double dot( Vector3D<T> b );
  Vector3D<T> cross( Vector3D<T> b );
  Vector3D<T> normalize();
  Vector3D<T> add( Vector3D<T> b);
  Vector3D<T> mult(float n);
  Vector3D<T> mult(Vector3D<T> b);
  Vector3D<T> rotate( Vector3D<T> rot );
  Vector3D<T> rotateX(float angle);
  Vector3D<T> rotateY(float angle);
  Vector3D<T> rotateZ(float angle);
  std::string toString();
  bool equals( Vector3D<T> v );
  T* toArray();

  static float toRadians( float degrees );
  static float toDegrees( float radians );
};

typedef Vector3D<float> Vector;

#include "Vector3D.hxx"

#endif
