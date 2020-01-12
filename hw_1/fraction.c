#include "fraction.h"
#include <cstdio>

Fraction add ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.den + a.den * b.num, a.den * b.den };
}

Fraction multiply ( Fraction a, Fraction b ) {
  return (Fraction) { a.num * b.num, a.den * b.den };
}

Fraction reduce ( Fraction a) {
  int n1, n2, i, gcd;
  gcd = 0;
  n1 = a.num;
  n2 = a.den;

  // 0 denominator scenario
  if (a.den == 0)
    return a;
  

  for(i=1; i <= n1 && i <= n2; ++i)
  {
      // Checks if i is factor of both integers
      if(n1%i==0 && n2%i==0)
          gcd = i;
  }
  printf("gcd: %d", &gcd);
  return (Fraction) { a.num/gcd, a.den/gcd};
}

// Recursive function to return gcd of a and b 
Fraction gcd(Fraction a) 
{ 
    // Everything divides 0  
    if (a.num == 0) 
       return a.den; 
    if (a.den == 0) 
       return a.num; 
  
    // base case 
    if (a.num == a.den) 
        return a.num; 
  
    // a is greater 
    if (a.num > a.den) 
        return gcd((Fraction) {a.num-a.den, a.den}); 
    return gcd((Fraction) {a.num, a.den-a.num}); 
} 