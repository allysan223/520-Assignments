#ifndef COMPLEX
#define COMPLEX

#include <iostream>

class Complex {
    public:
    Complex(double x, double y){
        real = x, imag = y;
    };
    Complex(double a) {
        real = a;
        imag = 0;
    };

    double magnitude() const;
    double re() const;
    double im() const;

    Complex conjugate() const;

    private:
    double real, imag;
}; 

bool operator<(const Complex& a, const Complex& b);
bool operator==(const Complex& a, const Complex& b);

Complex operator*(const Complex& a, const Complex& b);
Complex operator+(const Complex& a, const Complex& b);




#endif