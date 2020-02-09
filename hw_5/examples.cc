#include <exception>
#include "examples.h"
#include <cstring>
#include <iostream>

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

    // initalizes an array of booleans
    memset(prime, true, sizeof(prime)); 
  
    for (int p = 2; p*p<=n; p++) 
    { 
        // Checks if prime[p] is still true
        if (prime[p] == true) 
        { 
            //update to false since it is a multiple 
            for (int i=p*p; i<=n; i += p) 
                prime[i] = false; 
        } 
    }

    for (int p=2; p<=n; p++) 
       if (prime[p]) 
          v.push_back(p);

    return v;
}

vector<tuple<int,int>> twins(vector<int> nums){
    vector<tuple<int,int>> pairs;
    sort(nums.begin(),nums.end());
    for (int i =0; i < nums.size()-1; i++){
        //cout << "nums: " << nums[i] << ", " << nums[i+1] << "\n";
        if (abs(nums[i+1]) - abs(nums[i]) == 2)
            pairs.push_back( make_tuple(nums[i], nums [i+1]));
    }
    
    return pairs;
}

