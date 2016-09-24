#ifndef LIGHT_H
#define LIGHT_H

#include "color.h"
#include "point.h"

class Light {
public:
  Light(Point p, Color c) : cLight(p), col(c) {}
  
  Point center() const { return cLight; }
  Color color() const { return col; }

 protected:
  Point cLight;
  Color col;

};
#endif //LIGHT__H
