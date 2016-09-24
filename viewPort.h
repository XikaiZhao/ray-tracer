#ifndef VIEWPORT_H
#define VIEWPORT_H
/*******************************************************************************
  ViewPort

    functions
      d() returns distance from eye to screen
      w() returns width of the screen
      h() returns length of the screen

 * ****************************************************************************/
#include <iostream>
#include <vector>
#include "point.h"
#include "ray.h"

//#define DEBUG_VIEWPORT

class ViewPort {
public :
  ViewPort(); 
  ViewPort(Point e, Point d, Point x_direc, double s, double w = 0, double l = 0, unsigned int x = 10, unsigned int y = 10);  

  Point  viewPoint() const { return eye; }
  Point  viewDirection() const { return viewDirec; }

  double d() const { return distance; }
  double w() const { return width; }
  double h() const { return height; }
  unsigned int pixels(int i) const { return pixel[i]; }
  unsigned int numPixels() const { return pixel[0]*pixel[1]; }
  Point& pixel_coordinate(unsigned int i, unsigned int j); //(0,0) is top left
  
  Ray pixelToRay(unsigned int i, unsigned int j);

private :
  Point eye;
  Point viewDirec; 
  Point x_direc_screen;
  Point y_direc_screen;

  double distance; // distance from eye to screen

  double width;
  double height;
  unsigned int pixel[2];
  
  std::vector<Point> pixel_coordinates;

  void setup_screen();

#ifdef DEBUG_ViewPort
  unsigned int chkInd(unsigned int i, unsigned int m) {  
    if(i < 0 && i >= m) { 
      std::cerr << "Index out of range in Line: !( 0<=" << i << "<" << m << " )"; 
      std::cerr << " in file " <<__FILE__<< ", line " <<__LINE__
                << ", in function " <<__func__<<std::endl; 
      exit(1); 
    } 
    return i;
  }
#endif

#ifndef DEBUG_VIEWPORT
  unsigned int chkInd(unsigned int i, unsigned int m) { return i; }
#endif

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// inline functions
inline Point& ViewPort :: pixel_coordinate(unsigned int i, unsigned int j) {
  //(0,0) is top left
  return pixel_coordinates[chkInd(i,pixel[0])+chkInd(j,pixel[1])*pixel[0]];
}

#endif //VIEWPORT_H 
