#include "conversion.h"
#include <Math.h>

int decimalPart(float f, int m) {
  double frac;
  double intp;
  
  frac = modf(f, &intp);

  return (int)(f * m + 0.5);
}
