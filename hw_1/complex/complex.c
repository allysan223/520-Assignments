#include "complex.h"
#include <math.h>
#include <cstdio>

Complex add ( Complex a, Complex b ) {
    Complex temp;
    temp.real = a.real + b.real;
    temp.im = a.im + b.im;
  return temp;
}

Complex multiply ( Complex a, Complex b ) {
    Complex temp;
    temp.real = a.real * b.real - a.im * b.im;
    temp.im = a.real * b.im + a.im * b.real;
  return temp;
}

Complex negate ( Complex a) {
  return (Complex) { -a.real, -a.im };
}

double magnitude ( Complex a) {
  double mag;
  mag = pow(a.real, 2) + pow(a.im, 2);
  mag = sqrt(mag);
  return mag;
}