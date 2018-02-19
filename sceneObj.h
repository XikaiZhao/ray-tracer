#ifndef SCENEOBJ_H
#define SCENEOBJ_H

/******************************************************************************
 SceneObj
 *
 Sphere (Derived class)
   functions:
     Point normal(Point p) gives the outter unit vector;
     Color getColor(Point p);

 *******************************************************************************/

#include <vector>
#include "color.h"
#include "point.h"
#include "ray.h"

class SceneObj;
class Plane;
class Sphere;
class Triangle;
class Quadrilateral;

///////////////////////////////////////////////////////////////////////////////
//class SceneObj
class SceneObj {
public:
  virtual std::vector<double> intersection(Ray r) = 0 ;//return sorted vector
  virtual Point normal(Point p) = 0 ;
  virtual Color getColor(Point p) const = 0 ;  
  virtual double diffusion() const = 0 ;
  virtual double reflectivity() const = 0 ;
  virtual double specular()  const = 0 ;
  virtual double transparency()  const = 0 ; 
};


///////////////////////////////////////////////////////////////////////////////
//class Plane
class Plane : public SceneObj {
public:
  Plane();
  Plane(Point xx, Point yy, Point zz, Color c, 
        double diff = .5, double ref = .2, 
        double sp = .1, double trans = .4);

  std::vector<double> intersection(Ray r); 

  Point  normal(Point p) const { return unitNormal; }
  Color  getColor(Point p) const { return col; }
   
  double diffusion() const { return diffuse; } 
  double reflectivity() const { return reflect;}
  double specular() const { return spec; } 
  double transparency() const { return transparent; }

private:
  Point  x, y, z;
  Color  col;
  Point  unitNormal;
    
  double diffuse;
  double reflect;
  double spec;
  double transparent;
};


//////////////////////////////////////////////////////////////////////////////////
//class Sphere
class Sphere : public SceneObj {
public:
   Sphere();
   Sphere(Point ct, double rad, Color c, 
          double diff = .5, double ref = .2, 
          double sp = .1, double trans = .4);
   Sphere(Point ct, double rad, 
          std::vector<std::vector<Color> > c, 
          double diff = .5, double ref = .2, 
          double sp = .1, double trans = .4);

   std::vector<double> intersection(Ray r); //return sorted vector ascending order
   
   Point normal(Point p); //return outter unit normal vector;
   
   Color getColor(Point p) const;
   
   Point  sphereCenter() const { return center; }
   double sphereRadius() const { return radius; }
   double diffusion() const { return diffuse; } 
   double reflectivity() const { return reflect;}
   double specular() const { return spec; } 
   double transparency() const { return transparent; }

private:
    Point  center;
    double radius;
    Color  col;
    std::vector<std::vector<Color> > colmap;
    bool isMap;
    
    double diffuse;
    double reflect;
    double spec;
    double transparent;

};

///////////////////////////////////////////////////////////////////////////////////////
//class Triangle
class Triangle : public SceneObj {
 public:
  Triangle();
  Triangle(Point p1, Point p2, Point p3,
	   Color color,
	   double transparency = 0.1,
	   double reflectivity = 0.1,
	   double diffusion = 0.4,
	   double specular = 0.2); // CCW order (for normal vector)
  std::vector<double> intersection(Ray r); //return sorted vector
  Point normal(Point p) { return n; }
  Color getColor(Point p) const { return col; }
  double transparency() const { return transp; }
  double reflectivity() const { return refl; }
  double diffusion() const { return diff; }
  double specular() const { return spec; }
  
  bool isInTriangle(Point p) const;
  std::vector<double> transform(Point p, Point u, Point v) const;

 private:
  Point a, b, c;
  Point n; // unit normal vector
  Color col;
  double transp, refl, diff, spec;
  
};

///////////////////////////////////////////////////////////////////////////////////////
//class Quadrilateral
class Quadrilateral : public SceneObj {
 public:
  Quadrilateral();
  Quadrilateral(Point p1, Point p2, Point p3, Point p4, 
                Color color,
                double transparency = 0.1,
                double reflectivity = 0.1,
                double diffusion = 0.4,
                double specular = 0.2); // CCW order (for normal vector)
  Quadrilateral(Point p1, Point p2, Point p3, Point p4, 
                std::vector<std::vector<Color> > color,
                double transparency = 0.1,
                double reflectivity = 0.1,
                double diffusion = 0.4,
                double specular = 0.2); // CCW order (for normal vector)
  
  std::vector<double> intersection(Ray r); //return sorted vector
  Point normal(Point p) { return n; }
  Color getColor(Point p) const;
  double transparency() const { return transp; }
  double reflectivity() const { return refl; }
  double diffusion() const { return diff; }
  double specular() const { return spec; }

 private:
  Point a, b, c, d;
  Point n; // normal vector
  Color col;
  std::vector<std::vector<Color> > colmap;
  double transp, refl, diff, spec;

  Triangle trang1, trang2;
  bool isMap;
};

#endif //SCENEOBJ_H
