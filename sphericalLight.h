#ifndef SPHERICALLIGHT_H
#define SPHERICALLIGHT_H

#include "point.h"
#include "color.h"
#include "light.h"
#include "sceneObj.h"
#include <stdlib.h>
#include <time.h>

class SphericalLight : public Light, public Sphere {
 public:
  SphericalLight(Point p, double r, Color c) : Light(p, c), Sphere(p, r, c), rad(r) {}
  double radius() const { return rad; }
  Point randomPointOnLight(Point p);
 private:
  double rad;
};


/**
 * The cross section of the spherical light with the line from p
 * to the light's center is a disk.
 * @return A random point on this disk.
 */
inline Point SphericalLight::randomPointOnLight(Point p) {
  Point e2 = (Light::center()-p).arbitraryPerp();
  e2 = e2*radius();
  Point e3 = (Light::center()-p).cross(e2);
  e3.normalize();
  e3 = e3*radius();

  //std::cout << e2 << ", " << e3 << std::endl;
  //srand(time(NULL));
  double x, y;
  do {
    x = ((double)rand())/((double)RAND_MAX)*2 - 1;
    y = ((double)rand())/((double)RAND_MAX)*2 - 1;
  } while (x*x + y*y > 1);

  return Light::center() + (e2 * x + e3 * y);
}
#endif // SPHERICALLIGHT_H
