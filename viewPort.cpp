#include "viewPort.h"
#include <cmath>
#include <iostream>

ViewPort :: ViewPort() : eye(1,0,0), viewDirec(-1,0,0), x_direc_screen(0,1,0), y_direc_screen(0,0,1) { 
  distance = 1;
  width = 10; height = 10;  
  pixel[0] = 10; pixel[1] = 10; 
  setup_screen();
}

/**
 *
 * @param x Number of pixels in x direction.
 */
ViewPort :: ViewPort(Point e, Point d, Point x_direc, double s, double w, double l, unsigned int x, unsigned int y) 
{ 
  eye = e; viewDirec = d; 
  viewDirec.normalize();
  x_direc_screen = x_direc;
  x_direc_screen.normalize();// = x_direc/x_direc.l2Norm();
  if (fabs(x_direc_screen.dot(viewDirec)) > 1e-4) { 
    std::cerr<<"in file: "<<__FILE__<<", line: "<<__LINE__<<", not perpendicular!"<<std::endl; 
    exit(1); 
  }
  y_direc_screen = d.cross(x_direc) * -1;
  std::cout << "y_direc_screen: " << y_direc_screen << std::endl;
  y_direc_screen.normalize();// = y_direc_screen/y_direc_screen.l2Norm();

  distance = s;
  width = w; height = l; 
  pixel[0] = x; pixel[1] = y;

  setup_screen();
} 

void ViewPort :: setup_screen() {
  pixel_coordinates.resize(pixel[0]*pixel[1]);
  double dx = width/pixel[0], dy = height/pixel[1];

  Point center = eye;
  center += viewDirec*distance;
 
  pixel_coordinates[0] = center+y_direc_screen*(pixel[1]-1)/2.*dy-x_direc_screen*(pixel[0]-1)/2.*dx;
  
  for (unsigned int j=0; j<pixel[1]; j++)
  for (unsigned int i=0; i<pixel[0]; i++) {
    pixel_coordinates[i+j*pixel[0]] = pixel_coordinates[0]+x_direc_screen*(i*dx)-y_direc_screen*(j*dy);
  }
}

Ray ViewPort :: pixelToRay( unsigned int i, unsigned int j ) {
  Point dir = pixel_coordinate(i,j) - eye;
  Ray r(eye, dir);
  
  return r;
}

