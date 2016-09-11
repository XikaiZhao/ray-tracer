#ifndef VIEWPORT_H
#define VIEWPORT_H
/*******************************************************************************
  ViewPort
 *
 *
 * ****************************************************************************/
#include <iostream>
#include <vector>
#include "point.h"

//#define DEBUG_VIEWPORT
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

class ViewPort {
public :
  ViewPort(); 
  ViewPort(Point e, Point d, Point x_direc, double w = 0, double l = 0, unsigned int x = 10, unsigned int y = 10);  

  Point  viewPoint() const {return eye;}
  Point  viewDirection() const {return viewDirec;}
  double w() const {return width;}
  double h() const {return height;}
  unsigned int pixels(int i) const {return pixel[i];}

  Point& pixel_coordinate(unsigned int i, unsigned int j); //(0,0) is top left

private :
  Point eye;
  Point viewDirec; //magnitude is distance of eye from screen
  Point x_direc_screen;
  Point y_direc_screen;
  double width;
  double height;
  unsigned int pixel[2];
  
  std::vector<Point> pixel_coordinates;

  void setup_screen();
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// inline functions
inline Point& ViewPort :: pixel_coordinate(unsigned int i, unsigned int j) {
  //(0,0) is top left
  return pixel_coordinates[chkInd(i,pixel[0])+chkInd(j,pixel[1])*(pixel[0]+1)];
}

#endif //VIEWPORT_H 
