#include <cmath>
#include <omp.h>
#include <pthread.h>
#include "raytracer.h"

Color Raytracer :: compute(Ray r, int depth, bool reflection) {
  double t = Scene::VIEW_LIMIT;
  SceneObj* ns = NULL;

  for (unsigned int i=0; i<scene.sizeObj(); ++i){
    std::vector<double> inter = scene.object(i)->intersection(r);
    if (inter.size() != 0){
      double closest = inter[0];
      if (closest < t && closest >1e-4) {
        t = closest;
        ns = scene.object(i);
      }
    }
  }

  Color total;
  total.init(0,0,0);
  if (ns == NULL) {
    total.init(0,0,0);
  }
  else {
    Point p = r.trace(t);
    for (unsigned int i=0; i<scene.sizeLight(); ++i) {
      if (scene.shining(scene.light(i), p)) {
//        double distToLight = (scene.light(i).center()-p).square();
//        double diffusionFactor = std::min(1.,6/(5+distToLight));
        total = total + computeDiffusion(ns, scene.light(i), p);
        total = total + computeSpecular(ns, scene.light(i), p);       
      }
    }

    for (unsigned int i=0; i<scene.sizeSphericalLight(); ++i) {
      SphericalLight light = scene.sphericalLight(i);
      double c = scene.proportionShining(light, p);
      total = total + computeDiffusion(ns, scene.sphericalLight(i), p)*c;
      total = total + computeSpecular(ns, scene.sphericalLight(i), p)*c;
    }
    if (depth >0 && reflection) {
      total = total + computeReflection(ns, r, p, depth, reflection);
    }
    Color ambient;
    ambient = ns->getColor(p)*.1;
    total = total+ambient;
  }
  
  return total;
}

Color* Raytracer :: render() {
  Color* grid = new Color[view->numPixels()]; 
  
  omp_set_num_threads(4);
  #pragma omp parallel for collapse(2)
  for (unsigned int j=0; j<view->pixels(1); ++j) 
  for (unsigned int i=0; i<view->pixels(0); ++i) {
    Ray r = view->pixelToRay(i,j);
    grid[i+j*view->pixels(0)] = compute(r, 7, true);
  }

  return grid;
}

Color Raytracer :: computeDiffusion(SceneObj* obj, Light light, Point p) {
  Point normalVec = obj->normal(p);
  Point ptToEye = view->viewPoint()-p;
  ptToEye.normalize();

  Point ptToLight = light.center()-p;
  ptToLight.normalize();

  Color diffuseCol;
  diffuseCol = (obj->getColor(p))*(obj->diffusion())*pow(normalVec.dot(ptToLight),2);
  
  return diffuseCol;
}

Color Raytracer :: computeSpecular(SceneObj* obj, Light light, Point p) {
  Point normalVec = obj->normal(p);
  Point ptToEye = view->viewPoint()-p;
  ptToEye.normalize();

  Point ptToLight = light.center()-p;
  Point reflect = ptToLight-(ptToLight - normalVec*ptToLight.dot(normalVec))*2;
  reflect.normalize();

  Color specularCol;
  specularCol = (obj->getColor(p))*(obj->specular())*pow(std::max(0.,ptToEye.dot(reflect)),7);
  return specularCol;
}

Color Raytracer :: computeReflection(SceneObj* obj, Ray ray, Point p, int depth, bool reflection) {
  Point normalVec = obj->normal(p);

  Point reverseRay = ray.rayDirect()*(-1);
  Point reflect = reverseRay - (reverseRay - normalVec*reverseRay.dot(normalVec))*2;
  reflect.normalize();
  
  Ray r_reflect(p+ reflect*1e-6, reflect);
  Color reflectCol = compute(r_reflect,depth-1, reflection);
  
  int r,g,b;
  r = (obj->getColor(p)).getRed()*reflectCol.getRed()/255;
  g = (obj->getColor(p)).getGreen()*reflectCol.getGreen()/255;
  b = (obj->getColor(p)).getBlue()*reflectCol.getBlue()/255;
  
  Color newCol; newCol.init(r,g,b);
  newCol = newCol * (obj->reflectivity());
  return newCol;
}

