#include <math.h>
#include "complex.h"

double Complex::magnitude() const {

    return sqrt(real*real + imag*imag);

}

double Complex::re() const {
    return real;
}

double Complex::im() const {
    return imag;
}

Complex Complex::conjugate() const {
    return Complex(real, -imag);
}

bool operator<(const Complex& a, const Complex& b) {

    return a.magnitude() < b.magnitude();

}

bool operator==(const Complex& a, const Complex& b) {
    return (a.re() == b.re()) && (a.im() == b.im());
}

Complex operator*(const Complex& a, const Complex& b) {
    double rePart = a.re() * b.re() - a.im() * b.im();
    double imPart = a.re() * b.im() + a.im() * b.re();
  return Complex (rePart, imPart);
}

Complex operator+(const Complex& a, const Complex& b) {
    double rePart = a.re() + b.re();
    double imPart = a.im() + b.im();
  return Complex (rePart, imPart);
}

// double Complex::re() {
//      return this->re;
// }