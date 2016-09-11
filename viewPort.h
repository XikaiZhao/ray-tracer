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

//#define DEBUG_POINT
#ifdef DEBUG_POINT
#include <stdlib.h>
#endif

class Point;
class ViewPoint;

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//Point
class Point {
public:
  double value[3];

  Point(double xx=0, double yy=0, double zz=0) { value[0] = xx; value[1] = yy; value[2] = zz; }
  Point(const Point& p) { value[0] = p.value[0]; value[1] = p.value[1]; value[2] = p.value[2]; }
  void init(const Point& p) { value[0] = p.value[0]; value[1] = p.value[1]; value[2] = p.value[2]; }

  double square();
  double l2Norm();

  double  operator[] (int i) const { return value[chkInd(i)]; }
  double& operator[] (int i) { return value[chkInd(i)]; }
  double  operator() (int i) const { return value[chkInd(i)]; }
  double& operator() (int i) { return value[chkInd(i)]; }

  Point& operator= (const Point& p) { init(p); return *this;}

  Point& operator+= (const Point& p);
  Point& operator-= (const Point& p);
  
  double dot(const Point& p);
  Point cross(const Point& p);
  

protected:
  int chkInd(int i) const {  // index check if DEBUG_ARRAY is defined
    #ifdef DEBUG_POINT
        if(i<0 || i>2) {
            std::cerr << "Index out of range in Point: !( 0<="
            << i << "<=2" << " )" << std::endl;
            exit(1);
        }
    #endif
    return i;
  };
};

std::ostream& operator<< (std::ostream&, const Point&);

///////////////////////////////////////////////////////////////////////////////////////////////////////////
//ViewPort
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
inline Point :: Point& operator+= (const Point& p){
  for (int k=0;k<3; k++) {
    value[k] += p.value[k];
  }
  return *this;
}

inline Point :: Point& operator-= (const Point& p){ 
  for (int k=0;k<3; k++) {
    value[k] -= p.value[k];
  }
  return *this;
}

#endif //VIEWPORT_H 
