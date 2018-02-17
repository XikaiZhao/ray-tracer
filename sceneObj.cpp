#include <cmath>
#include "sceneObj.h"
#include "scene.h"

/////////////////////////////////////////////////////////////////////////////////////////////////////
//class Plane
Plane :: Plane() : x(1,0,0), y(0,1,0), z(0,0,0) {
  col.init(250,50,50);
  radius = 1.0;
  diffuse = 0.4;
  reflect = 0.1;
  transparent = 1.0;
  spec = 0.1;
  unitNormal = (x-z).cross(y-z);
  unitNormal.normalize();
}

Plane :: Plane(Point xx, Point yy, Point zz, Color c, double diff, double ref, double sp, double trans): 
  x(xx), y(yy), z(zz), col(c), diffuse(diff), reflect(ref), spec(sp), transparent(trans) {
  unitNormal = (x-z).cross(y-z);
  unitNormal.normalize();
}

std::vector<double> Plane :: intersection(Ray r) {
  double rayDotNormal = unitNormal.dot(r.rayDirect());
  if (rayDotNormal < 1e-6) return {};
  else {
    double t;
    t = -unitNormal.dot(r.rayInitPt()-z)/rayDotNormal;
    if (t < 1e-6) return {};
    return {t};
  }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////
//class Sphere
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

/////////////////////////////////////////////////////////////////////////////////////////////////////
//class Triangle
Triangle :: Triangle(Point p1, Point p2, Point p3,
		     Color color,
		     double transparency,
		     double reflectivity,
		     double diffusion,
		     double specular)
  : a(p1), b(p2), c(p3), col(color), transp(transparency),
    refl(reflectivity), diff(diffusion), spec(specular) {
  n = (b - a).cross(c - a);
  n.normalize();
}

std::vector<double> Triangle :: intersection(Ray r) {
  // First find intersection of the ray with the plane.
  // Solve for t:
  // n . ((x,y,z) - a) = 0
  // where (x, y, z) = r.InitPt() + t * r.rayDirect()
  // So n . (r.InitPt() + t * r.rayDirect() - a) = 0
  // t * (n . r.rayDirect()) = n . (a - r.InitPt())
  // t = n . (a - r.InitPt()) / (n . r.rayDirect())
  double denom = n.dot(r.rayDirect());
  double numer = n.dot(a - r.rayInitPt());
  double t = numer / denom;
  if (t < 1e-8 || t > Scene::VIEW_LIMIT || fabs(denom) < 1e-10) {
    return {};
  } else {
    Point p = r.trace(t);
    // Check that point is inside triangle.
    double det = (-(a[2]*b[1]*c[0]) + a[1]*b[2]*c[0]
		  + a[2]*b[0]*c[1] - a[0]*b[2]*c[1]
		  - a[1]*b[0]*c[2] + a[0]*b[1]*c[2]);
    double t1 = (-(b[2]*c[1]*p[0]) + b[1]*c[2]*p[0]
                + b[2]*c[0]*p[1] - b[0]*c[2]*p[1]
		 - b[1]*c[0]*p[2] + b[0]*c[1]*p[2])/det;
    double t2 = (a[2]*c[1]*p[0] - a[1]*c[2]*p[0]
              - a[2]*c[0]*p[1] + a[0]*c[2]*p[1]
	       + a[1]*c[0]*p[2] - a[0]*c[1]*p[2])/det;
    double t3 = (-(a[2]*b[1]*p[0]) + a[1]*b[2]*p[0]
                + a[2]*b[0]*p[1] - a[0]*b[2]*p[1]
	       - a[1]*b[0]*p[2] + a[0]*b[1]*p[2])/det;
    if (0 <= t1 && t1 <= 1 &&
	0 <= t2 && t2 <= 1 &&
	0 <= t3 && t3 <= 1) {
      return {t}; // is inside triangle
    } else {
      return {};
    }
  }
}
