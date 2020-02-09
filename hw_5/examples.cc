#include <exception>
#include "examples.h"
#include <cstring>

using namespace std;

void sort_by_magnitude(vector<double> &v){
    sort(
        v.begin(),
        v.end(),
        [](double &a,  
                double &b)
                { 
                     return ( abs(a) < abs(b) );
                }
    ); 
}

vector<int> primes(int n) {
    vector<int> v;
    bool prime[n+1]; 
    memset(prime, true, sizeof(prime)); 
  
    for (int p=2; p*p<=n; p++) 
    { 
        // If prime[p] is not changed, then it is a prime 
        if (prime[p] == true) 
        { 
            // Update all multiples of p greater than or  
            // equal to the square of it 
            // numbers which are multiple of p and are 
            // less than p^2 are already been marked.  
            for (int i=p*p; i<=n; i += p) 
                prime[i] = false; 
        } 
    }

    for (int p=2; p<=n; p++) 
       if (prime[p]) 
          v.push_back(p);

    return v;
}

