#include "point.h"

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

