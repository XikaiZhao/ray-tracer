
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "color.h"
#include "light.h"
#include "sphericalLight.h"
#include "ray.h"
#include "sceneObj.h"

struct Intersection {
  SceneObj* s;
  double t;
};

class Scene {
 public:
  static const double VIEW_LIMIT;
  
  void addObject(SceneObj* obj) { objects.push_back(obj); }
  void addLight(Light light) { lights.push_back(light); }
  void addSphericalLight(SphericalLight light) {
    sphericalLights.push_back(light);
  }

  unsigned int sizeObj() { return objects.size(); }
  unsigned int sizeLight() { return lights.size(); }
  unsigned int sizeSphericalLight() { return sphericalLights.size(); }
  
  SceneObj* object( int i );
  Light light( int i );
  SphericalLight sphericalLight(int i) { return sphericalLights[i]; }

  bool shining(Light light, Point p);
  Intersection intersection(Ray r);
  double proportionShining(SphericalLight light, Point p, int trials=20);
  
 private:
  std::vector<SceneObj*> objects;
  std::vector<Light> lights;
  std::vector<SphericalLight> sphericalLights;
  bool lineSegmentIntersects(Point p1, Point p2);
  
};


////////////////////////////////////////////////////////////////////////inline functions
inline SceneObj* Scene :: object(int i) {
  return objects[i];
}

inline Light Scene::light(int i) {
  return lights[i];
}







#endif //SCENE_H
