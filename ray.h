#ifndef RAY_H
#define RAY_H

#include "point.h"

class Ray {
public:
  Ray(Point p, Point d) : initPt(p), direct(d) { direct.normalize(); }
  
  Point rayInitPt() const { return initPt; }
  Point rayDirect() const { return direct; }
  
  Point trace(double t); 

private:
  Point initPt;
  Point direct; // unit vector
};

/////////////////////////////////////////////////////////////////////////////////////////////
// inline function
inline Point Ray :: trace(double t) {
  Point newPt;
  newPt = initPt + direct*t;
  return newPt;
}

#endif //RAY_H




