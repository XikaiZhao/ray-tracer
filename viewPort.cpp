#include "viewPort.h"
#include <cmath>

ViewPort :: ViewPort() : eye(1,0,0), viewDirec(-1,0,0), x_direc_screen(0,1,0), y_direc_screen(0,0,1) { 
  width = 10; height = 10;  
  pixel[0] = 10; pixel[1] = 10; 
  setup_screen();
}

ViewPort :: ViewPort(Point e, Point d, Point x_direc, double w, double l, unsigned int x, unsigned int y) 
{ 
  eye = e; viewDirec = d; 
  x_direc_screen = x_direc/x_direc.l2Norm();
  if (x_direc_screen.dot(viewDirec/viewDirec.l2Norm()) < 1e-6) { 
    std::cerr<<"in file: "<<__FILE__<<"not perpendicular!"<<std::endl; 
    exit(1); 
  }
  y_direc_screen = d.cross(x_direc);
  y_direc_screen = y_direc_screen/y_direc_screen.l2Norm();

  width = w; height = l; 
  pixel[0] = x; pixel[1] = y;

  setup_screen();
} 

void ViewPort :: setup_screen() {
  pixel_coordinates.resize((pixel[0]+1)*(pixel[1]+1));
  double dx = width/pixel[0], dy = height/pixel[1];

  Point center = eye;
  center += viewDirec;
 
  pixel_coordinates[0] = center+y_direc_screen*pixel[1]/2.*dy-x_direc_screen*pixel[0]/2.*dx;
  for (unsigned int j=0; j<=pixel[1]; j++)
  for (unsigned int i=0; i<=pixel[0]; i++) {
    pixel_coordinates[i+j*(pixel[0]+1)] = pixel_coordinates[0]+x_direc_screen*(i*dx)-y_direc_screen*(j*dy);
  }
}

