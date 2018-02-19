#include <cmath>
#include "sceneObj.h"
#include "scene.h"

using namespace std;

/////////////////////////////////////////////////////////////////////////////////////////////////////
//class Plane
Plane :: Plane() : x(1,0,0), y(0,1,0), z(0,0,0) {
  col.init(250,50,50);
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

vector<double> Plane :: intersection(Ray r) {
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
  center(ct), radius(rad), col(c), diffuse(diff), reflect(ref), spec(sp), transparent(trans) 
{
  isMap = false;
};

Sphere :: Sphere(Point ct, double rad, vector<vector<Color> > c, 
                 double diff, double ref, double sp, double trans) : 
  center(ct), radius(rad), colmap(c), diffuse(diff), reflect(ref), spec(sp), transparent(trans) 
{
  isMap = true;
};

Color Sphere :: getColor(Point p) const {
  if (isMap) {
    double psi = atan2(p[1]-center[1], p[0]-center[0]) + M_PI,
           theta = acos((p[2]-center[2])/radius);
    int y = nearbyint(theta/M_PI*colmap.size());
    int x = nearbyint(psi/(2*M_PI)*colmap[0].size());

    y = min(y, (int)colmap.size()-1);
    x = min(x, (int)colmap[0].size()-1);
    return colmap[y][x];
  } else {
    return col; 
  }
}

Point Sphere :: normal(Point p) {
  Point normal = p-center;
  if (fabs(normal.l2Norm()-radius) > 1e-6) {
    cerr<<"Point need to be on the sphere!"<<endl;
    exit(1);
  }
  normal.normalize();
  return normal;
}

vector<double> Sphere :: intersection(Ray r) {
  Point v = r.rayInitPt()-center;
  double temp =pow(v.dot(r.rayDirect()),2)- (v.square()-pow(radius,2));
  if (temp < 0) return {};
  
  vector<double> intersects; 
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
Triangle :: Triangle() : a(0,0,0), b(1,0,0), c(0,1,0) {
  col.init(250,50,50);
  transp = 1.0;
  refl = 0.1;
  diff = 0.4;
  spec = 0.1;
  n = (b - a).cross(c - a);
  n.normalize();
}

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

bool Triangle :: isInTriangle(Point p) const {
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
  return (0 <= t1 && t1 <= 1 && 
          0 <= t2 && t2 <= 1 &&
	  0 <= t3 && t3 <= 1);
}

vector<double> Triangle :: intersection(Ray r) {
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
    if (isInTriangle(p)) {
      return {t}; // is inside triangle
    } else {
      return {};
    }
  }
}

// p = a u + b v
// return {a,b}
vector<double> Triangle :: transform(Point p, Point u, Point v) const {
  vector<double> res(2);
  res[0] = 
    ((-(u[0]*v[0]) - u[1]*v[1] - u[2]*v[2])*(u[0]*p[0] + u[1]*p[1] + u[2]*p[2]))/
     (-pow(u[0]*v[0] + u[1]*v[1] + u[2]*v[2],2) + 
       (pow(u[0],2) + pow(u[1],2) + pow(u[2],2))*
        (pow(v[0],2) + pow(v[1],2) + pow(v[2],2))) + 
    ((pow(u[0],2) + pow(u[1],2) + pow(u[2],2))*(v[0]*p[0] + v[1]*p[1] + v[2]*p[2]))/
     (-pow(u[0]*v[0] + u[1]*v[1] + u[2]*v[2],2) + 
       (pow(u[0],2) + pow(u[1],2) + pow(u[2],2))*
        (pow(v[0],2) + pow(v[1],2) + pow(v[2],2)));
  res[1] =
    ((pow(v[0],2) + pow(v[1],2) + pow(v[2],2))*(u[0]*p[0] + u[1]*p[1] + u[2]*p[2]))/
     (-pow(u[0]*v[0] + u[1]*v[1] + u[2]*v[2],2) + 
       (pow(u[0],2) + pow(u[1],2) + pow(u[2],2))*
        (pow(v[0],2) + pow(v[1],2) + pow(v[2],2))) + 
    ((-(u[0]*v[0]) - u[1]*v[1] - u[2]*v[2])*(v[0]*p[0] + v[1]*p[1] + v[2]*p[2]))/
     (-pow(u[0]*v[0] + u[1]*v[1] + u[2]*v[2],2) + 
       (pow(u[0],2) + pow(u[1],2) + pow(u[2],2))*
        (pow(v[0],2) + pow(v[1],2) + pow(v[2],2)));

  return res;
} 

/////////////////////////////////////////////////////////////////////////////////////////////////////
//class Quadrilateral
Quadrilateral :: Quadrilateral() : a(0,0,0), b(1,0,0), c(1,1,0), d(0,1,0) {
  col.init(250,50,50);
  transp = 1.0;
  refl = 0.1;
  diff = 0.4;
  spec = 0.1;
  
  trang1 = Triangle(a, b, d, col, transp, refl, diff, spec);
  trang2 = Triangle(b, c, d, col, transp, refl, diff, spec);
  
  Point n1 = trang1.normal(a);
  n = n1;

  isMap = false;
}

Quadrilateral :: Quadrilateral(Point p1, Point p2,
                               Point p3, Point p4,
                               Color color,
                               double transparency,
                               double reflectivity,
                               double diffusion,
                               double specular)
  : a(p1), b(p2), c(p3), d(p4), col(color), transp(transparency),
    refl(reflectivity), diff(diffusion), spec(specular) 
{
  trang1 = Triangle(p1, p2, p4, col, transp, refl, diff, spec);
  trang2 = Triangle(p3, p4, p2, col, transp, refl, diff, spec);
  
  Point n1 = trang1.normal(p1),
        n2 = trang2.normal(p2);
  if (fabs(n1.dot(n2)) != 1) {
    cerr<<"Quadrilateral: the given points are not on the same plane!"<<endl;
    exit(1);
  }

  n = n1;
  isMap = false;
}

Quadrilateral :: Quadrilateral(Point p1, Point p2,
                               Point p3, Point p4,
                               vector<vector<Color> > color,
                               double transparency,
                               double reflectivity,
                               double diffusion,
                               double specular)
  : a(p1), b(p2), c(p3), d(p4), colmap(color), transp(transparency),
    refl(reflectivity), diff(diffusion), spec(specular) 
{
  trang1 = Triangle(p1, p2, p4, col, transp, refl, diff, spec);
  trang2 = Triangle(p3, p4, p2, col, transp, refl, diff, spec);
  
  Point n1 = trang1.normal(p1),
        n2 = trang2.normal(p2);
  if (fabs(n1.dot(n2)) != 1) {
    cerr<<"Quadrilateral: the given points are not on the same plane!"<<endl;
    exit(1);
  }

  n = n1;
  isMap = true;
}

vector<double> Quadrilateral :: intersection(Ray r) {
  vector<double> in1 = trang1.intersection(r);
  if (in1.empty()) return trang2.intersection(r);
  else return in1;
}

Color Quadrilateral :: getColor(Point p) const {
  if (isMap) {
    int y, x;
    if (trang1.isInTriangle(p)) {
      Point u = b-a, v = d-a;
      vector<double> ratio = trang1.transform(p-a, u, v);
      if (ratio[0] < 0 && ratio[1] < 0) {
        cout<<"a: "<<a<<", b: "<<b<<", d: "<<d<<endl;
        cout<<"point: "<<p<<endl;
        cout<<ratio[0]<<" "<<ratio[1]<<endl;
        exit(1);
      };
      y = nearbyint(ratio[1]*colmap.size()),
      x = nearbyint(ratio[0]*colmap[0].size());
    }
    else {
      assert(trang2.isInTriangle(p));
      vector<double> ratio = trang2.transform(p-c, d-c, b-c);
      if (ratio[0] < 0 && ratio[1] < 0) {
        cout<<"c: "<<c<<", d: "<<d<<", b: "<<b<<endl;
        cout<<"point: "<<p<<endl;
        cout<<ratio[0]<<" "<<ratio[1]<<endl;
        exit(1);
      };
      y = nearbyint((1-ratio[1])*colmap.size()),
      x = nearbyint((1-ratio[0])*colmap[0].size());
    }
    y = min(y, (int)colmap.size()-1);
    x = min(x, (int)colmap[0].size()-1);
    return colmap[y][x];
  } else {
    return col; 
  }
}

