#include "point.h"
#include <cmath>

double Point :: square() { return value[0]*value[0] + value[1]*value[1] + value[2]*value[2];}
double Point :: l2Norm() { return sqrt(value[0]*value[0] + value[1]*value[1] + value[2]*value[2]); }

void Point :: normalize() {
  double len = sqrt(value[0]*value[0] + value[1]*value[1] + value[2]*value[2]);
  if (len < 1e-6) {
    std::cerr << "In file: "<<__FILE__<<", line: "<<__LINE__<<", length is close to 0!"<<std::endl;
    exit(1);
  }
  for (int k=0; k<3; k++) {
    value[k] /= len;
  }
}

double Point :: dot(const Point& p) {
  double prod = 0;
  for (int k=0; k<3; k++) {
    prod += p(k)*value[k];
  }
  return prod;
}

Point Point :: cross(const Point& p) {
  Point c;
  c(0) = value[1]*p(2)-value[2]*p(1);
  c(1) = value[2]*p(0)-value[0]*p(2);
  c(2) = value[0]*p(1)-value[1]*p(0);
  return c;
}

Point Point :: arbitraryPerp () {
  Point perp(1,1,1);
  
  int k = 0;
  while (k<3) {
    if (fabs(value[k]) > 1e-6) {
      perp[k] = 0;
      for (int m=0; m<3; m++){
        if (m != k) {
          perp[k] -= value[m]*perp[m];
        }
      }
      perp[k] /= value[k];
      perp.normalize();
      return perp;
    }
    k++;
  }
  
  perp.normalize();
  return perp;
}

std::ostream&  operator<< (std::ostream& os, const Point& p) {
    os << "(" << p.value[0] << "," << p.value[1]  << "," << p.value[2] << ")" ;
    return os;
}

