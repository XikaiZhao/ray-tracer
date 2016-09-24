#include "color.h"

std::ostream& operator<< (std::ostream& os, const Color& col) {
  os << "(" <<col.getRed() << "," << col.getGreen() << "," << col.getBlue() << ")" ;
  return os;
}
