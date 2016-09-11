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

//#define DEBUG_POINT
#ifdef DEBUG_POINT
#include <stdlib.h>
#endif

class Point {
public:
  double value[3];

  Point(double xx=0, double yy=0, double zz=0) { value[0] = xx; value[1] = yy; value[2] = zz; }
  Point(const Point& p) { value[0] = p.value[0]; value[1] = p.value[1]; value[2] = p.value[2]; }
  void init(const Point& p) { value[0] = p.value[0]; value[1] = p.value[1]; value[2] = p.value[2]; }

  double square();
  double l2Norm();

  double  operator[] (int i) const { return value[chkInd(i)]; }
  double& operator[] (int i) { return value[chkInd(i)]; }
  double  operator() (int i) const { return value[chkInd(i)]; }
  double& operator() (int i) { return value[chkInd(i)]; }

  Point& operator= (const Point& p) { init(p); return *this;}
  
  Point  operator+ (const Point& p);
  Point  operator- (const Point& p);
  Point  operator* (const double c); 
  Point  operator/ (const double c); 
 
  Point& operator+= (const Point& p);
  Point& operator-= (const Point& p);
  
  double dot(const Point& p);
  Point cross(const Point& p);
  

protected:
  int chkInd(int i) const {  // index check if DEBUG_ARRAY is defined
    #ifdef DEBUG_POINT
        if(i<0 || i>2) {
            std::cerr << "Index out of range in Point: !( 0<="
            << i << "<=2" << " )" << std::endl;
            exit(1);
        }
    #endif
    return i;
  };
};

std::ostream& operator<< (std::ostream&, const Point&);


///////////////////////////////////////////////////////////////////////////////////////////////////////////
// inline functions
inline Point Point :: operator+ (const Point& p){
  Point res;
  for (int k=0;k<3; k++) {
    res[k] = value[k] + p.value[k];
  }
  return res;
}

inline Point Point :: operator- (const Point& p){ 
  Point res;
  for (int k=0;k<3; k++) {
    res[k] = value[k] - p.value[k];
  }
  return res;
}

inline Point Point :: operator* (const double c){ 
  Point res;
  for (int k=0;k<3; k++) {
    res[k] = value[k] * c;
  }
  return res;
}

inline Point Point :: operator/ (const double c){ 
  if (c < 1e-10) { std::cerr<<"Divided by a # close to 0!"<<std::endl; exit(1);}
  
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
