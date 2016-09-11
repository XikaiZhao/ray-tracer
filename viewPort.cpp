#include "viewPort.h"
#include <cmath>

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Point
double Point :: square() { return pow(value[0],2) + pow(value[1],2) + pow(value[2],2);}
double Point :: l2Norm() { return sqrt(square()); }

double Point :: dot(const Point& p) {
  double prod = 0;
  for (int k=0; k<3; k++) {
    prod += p.value[k]*value[k];
  }
  return prod;
}

double Point :: cross(const Point& p) {
  Point c;
  c(0) = value[2]*p(3)-value[3]*p(2);
  c(1) = value[3]*p(1)-value[1]*p(3);
  c(2) = value[1]*p(2)-value[2]*p(1);
  return c;
}

std::ostream& operator<< (std::ostream& os, const Point& p) {
    os << "(" << p.value[0] << "," << p.value[1]  << "," << p.value[2] << ")" ;
    return os;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//ViewPoint
ViewPort :: ViewPort() : eye(1,0,0), viewDirec(-1,0,0), x_direc_screen(0,1,0), y_direc_screen(0,0,1) { 
  width = 10; height = 10;  
  pixel[0] = 10; pixel[1] = 10; 
}

ViewPort :: ViewPort(Point e, Point d, Point x_direc, double w = 10, double l = 10, 
    unsigned int x = 10, unsigned int y = 10) 
{ 
  eye = e; viewDirec = d; x_direc_screen = x_direc/x.l2Norm;
  if (x_direc_screen.dot(viewDirec/viewDirec.l2Norm) < 1e-6) { 
    std::cerr<<"in file: "<<__FILE__<<"not perpendicular"<<std::endl; 
    exit(1); 
  }
  y_direc_screen

  width = w; height = l; 
  pixel[0] = x; pixel[1] = y;
} 

void ViewPoint :: setup_screen() {
  pixel_coordinates.resize((pixel[0]+1)*(pixel[1]+1));

  Point center = eye;
  center += viewDirec;
  
  pixel_coordinates[0](0) = center(0)-
}

