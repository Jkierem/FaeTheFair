#ifndef __VECTOR3D__H__
#define __VECTOR3D__H__

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
  T dot( Vector3D<T> b );
  Vector3D<T> cross( Vector3D<T> b );
  Vector3D<T> normalize();
  Vector3D<T> add( Vector3D<T> b);
};

typedef Vector3D<float> Vector;

#include "Vector3D.hxx"

#endif
