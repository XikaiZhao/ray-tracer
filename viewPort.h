#ifndef VIEWPORT_H
#define VIEWPORT_H
/*******************************************************************************
  Point
  ViewPort
 *
 *
 * ****************************************************************************/
#include <iostream>
#include <vector>
#include "point.h"

class ViewPort {
public :
  ViewPort(); 
  ViewPort(Point e, Point d, Point x_direc, double w = 0, double l = 0, unsigned int x = 10, unsigned int y = 10);  

  Point& viewPoint() const {return eye;}
  Point& viewDirection() const {return viewDirec;}
  double w() const {return width;}
  double h() const {return height;}
  unsigned int pixels(int i) const {return pixel[i];}

  Point pixel_coordinate(unsigned int i, unsigned int j); //(0,0) is top left

private :
  Point eye;
  Point viewDirec; //magnitude is distance of eye from screen
  Point x_direc_screen;
  Point y_direc_screen;
  double width;
  double height;
  unsigned int[2] pixel;
  
  std::vector<Point> pixel_coordinates;

  void setup_screen();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
// inline functions
Point ViewPort :: pixel_coordinate(unsigned int i, unsigned int j) {
  //(0,0) is top left
  return pixel_coordinates[i+j*pixel[0]];
}

#endif //VIEWPORT_H 
