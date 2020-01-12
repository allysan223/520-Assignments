#include "fraction.h"
#include <cstdio>

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

Fraction reduce ( Fraction a) {
  if (a.num == 0)
    return (Fraction) { a };
  int commonDenom = gcd(a.num, a.den);
  return (Fraction) { a.num/commonDenom, a.den/commonDenom };
}

// Recursive function to return gcd of a and b 
int gcd(int a, int b) 
{ 
    if (b == 0) 
        return a; 
    return gcd(b, a % b);  
} 