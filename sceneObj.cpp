#include <cmath>
#include "sceneObj.h"

Sphere :: Sphere() : center(0,0,0) {	
  col.init(250,50,50);
  radius = 1.0;
  diffuse = 0.4;
  reflect = 0.1;
  transparent = 1.0;
  spec = 0.1;
}
   
Sphere :: Sphere(Point ct, double rad, Color c, double diff, double ref, double sp, double trans) : 
  center(ct), radius(rad), col(c), diffuse(diff), reflect(ref), spec(sp), transparent(trans) {};

Point Sphere :: normal(Point p) {
  Point normal = p-center;
  if (fabs(normal.l2Norm()-radius) > 1e-6) {
    std::cerr<<"Point need to be on the sphere!"<<std::endl;
    exit(1);
  }
  normal.normalize();
  return normal;
}

std::vector<double> Sphere :: intersection(Ray r) {
  Point v = r.rayInitPt()-center;
  double temp =pow(v.dot(r.rayDirect()),2)- (v.square()-pow(radius,2));
  if (temp < 0) return {};
  
  std::vector<double> intersects; 
  double t1 = -v.dot(r.rayDirect()) - sqrt(temp),
         t2 = -v.dot(r.rayDirect()) + sqrt(temp);

  if (t1 > 1e-4)  { 
    intersects.push_back(t1); 
    intersects.push_back(t2);
    return intersects;
  }
  else if (t2 < 1e-4) return {};
  else {
    intersects.push_back(t2);
    return intersects;
  }
}
