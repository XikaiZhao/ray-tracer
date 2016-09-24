#ifndef COLOR_H
#define COLOR_H

#include <iostream>

class Color {
 public:
  Color() {
    red = 0; green = 0; blue = 0; alpha = 0;
  }

  int getRed() const { return red; }
  int getGreen() const { return green; }
  int getBlue() const { return blue; }
  int getAlpha() const { return alpha; }

  void init(int r, int g, int b, int a) {
    init(r, g, b);
    alpha = a;
  }

  void init(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
  }

  Color operator*(double c);
  Color operator+(Color c);
  
 private:
  int red, green, blue, alpha;
};

std::ostream& operator<< (std::ostream& os, const Color& col); 

/////////////////////////////////////////////////////////////////////////////////////////////
//inline function
inline Color Color::operator*(double c) {
  if (c < -0.0001) {
    std::cerr << "Can't scale colour by negative number. c = " << c<<std::endl;
    exit(1);
  }
  Color nC;
  nC.init(std::min((int)(c*red), 255),
	  std::min((int)(c*green), 255),
	  std::min((int)(c*blue), 255),
	  std::min((int)(c*alpha), 255));
  return nC;     
}

inline Color Color::operator+(Color c) {
  Color nC;
  nC.init(std::min(red + c.red, 255),
	   std::min(green + c.green, 255),
	   std::min(blue + c.blue, 255),
	   std::min(alpha + c.alpha, 255));
  return nC;
}
#endif
