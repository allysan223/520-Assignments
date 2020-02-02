#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(re*re + im*im);

}

double Complex::real() const {
    return re;
}

double Complex::imag() const {
    return im;
}

Complex Complex::conjugate() const {
    return Complex(re, -im);
}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

Complex operator*(const Complex& a, const Complex& b) {
    double realPart = a.real() * b.real() - a.imag() * b.imag();
    double imagPart = a.real() * b.imag() + a.imag() * b.real();
  return Complex (realPart, imagPart);
}

// double Complex::re() {
//      return this->real;
// }