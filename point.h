#ifndef POINT_H
#define POINT_H

/******************************************************************************
 Point

  These are points in 3D.

  The  functions
    []  gives access to the value in the given direction
    init() fills the point with values from another point

******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <assert.h>

#define NDEBUG

class Point {
public:
  double value[3];

  Point(double xx=0, double yy=0, double zz=0) { value[0] = xx; value[1] = yy; value[2] = zz; }
  Point(const Point& p) { value[0] = p.value[0]; value[1] = p.value[1]; value[2] = p.value[2]; }
  void init(const Point& p) { value[0] = p.value[0]; value[1] = p.value[1]; value[2] = p.value[2]; }

  double  operator[] (int i) const { 
    assert(i >= 0 && i < 3);
    return value[i]; 
  }
  double& operator[] (int i) { 
    assert(i >= 0 && i < 3);
    return value[i];
  }
  double  operator() (int i) const { 
    assert(i >= 0 && i < 3);
    return value[i];
  }
  double& operator() (int i) { 
    assert(i >= 0 && i < 3);
    return value[i]; 
  }

  Point& operator= (const Point& p) { init(p); return *this;}
  
  Point  operator+ (const Point& p) const;
  Point  operator- (const Point& p) const;
  Point  operator* (const double c) const; 
  Point  operator/ (const double c) const; 
 
  Point& operator+= (const Point& p);
  Point& operator-= (const Point& p);
 
  double square();
  double l2Norm();
  
  void normalize();
  
  double dot(const Point& p);
  Point cross(const Point& p);
  
  Point arbitraryPerp();  // output a unit perpendicular vector
};

std::ostream&  operator<< (std::ostream& os, const Point& p); 


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// inline functions
inline Point Point :: operator+ (const Point& p) const{
  Point res;
  for (int k=0;k<3; k++) {
    res[k] = value[k] + p.value[k];
  }
  return res;
}

inline Point Point :: operator- (const Point& p) const{ 
  Point res;
  for (int k=0;k<3; k++) {
    res[k] = value[k] - p.value[k];
  }
  return res;
}

inline Point Point :: operator* (const double c) const{ 
  Point res;
  for (int k=0;k<3; k++) {
    res[k] = value[k] * c;
  }
  return res;
}

inline Point Point :: operator/ (const double c) const{ 
  if (c < 1e-10) { 
    std::cerr<<"in file"<<__FILE__<<", line"<<__LINE__<<"divided by a # close to 0!"<<std::endl; 
    exit(1);
  }
  
  Point res;
  for (int k=0;k<3; k++) {
    res[k] = value[k] / c;
  }
  return res;
}

inline Point& Point :: operator+= (const Point& p){
  for (int k=0;k<3; k++) {
    value[k] += p.value[k];
  }
  return *this;
}

inline Point& Point :: operator-= (const Point& p){ 
  for (int k=0;k<3; k++) {
    value[k] -= p.value[k];
  }
  return *this;
}

#endif // POINT_H
