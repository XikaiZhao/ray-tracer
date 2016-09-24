
#include "scene.h"
#include <vector>

const double Scene::VIEW_LIMIT = 1000000;

Intersection Scene::intersection(Ray r) {
  SceneObj* nS = NULL;
  double nT = VIEW_LIMIT;
  for (unsigned int i=0; i<objects.size(); ++i) {
    SceneObj* s = objects[i];
    std::vector<double> inter = s->intersection(r);
    if (inter.size() > 0) {
      double d = inter[0];
      if (d < nT) {
	nT = d;
	nS = s;
      }
    }
  }
  Intersection x = {};
  x.s = nS;
  x.t = nT;
  return x;
}

bool Scene::shining(Light light, Point p) {
 return ! lineSegmentIntersects(light.center(), p);
}

bool Scene::lineSegmentIntersects(Point p1, Point p) {
  Ray r(p, p1 - p);
  double distLightToP = (p1 - p).l2Norm();
  for (unsigned int i=0; i<objects.size(); ++i) {
    SceneObj* s = objects[i];
    std::vector<double> inter = s->intersection(r);
    for (unsigned int j=0; j<inter.size(); ++j) {
      double t = inter[j];
      if (0.0 < t && t < distLightToP)
	return true; // object between point and light
    }
  }
  return false;
}

double Scene::proportionShining(SphericalLight light, Point p, int trials) {
  int numShining = 0;
  for (int i=0; i<trials; i++) {
    Point ptOnLight = light.randomPointOnLight(p);
    if ( ! lineSegmentIntersects(ptOnLight, p))
      numShining += 1;
  }
  return numShining * 1.0 / trials;
}
