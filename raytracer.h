#ifndef RAYTRACER_H
#define RAYTRACER_H
#include "color.h"
#include "scene.h"
#include "viewPort.h"

class Raytracer {
public:
  Raytracer() {}
  Raytracer(Scene sc, ViewPort* v) : scene(sc), view(v) {}

  Color compute(Ray r, int depth, bool reflection);
  Color* render();

private:
  Scene scene;
  ViewPort* view;

  Color computeDiffusion(SceneObj* obj, Light light, Point p); 
  Color computeSpecular(SceneObj* obj, Light light, Point p); 
  Color computeReflection(SceneObj* obj, Ray r, Point p, int depth, bool reflection);
};
#endif //RAYTRACER_H
