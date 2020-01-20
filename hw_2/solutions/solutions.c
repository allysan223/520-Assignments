#include "solutions.h"
#include <cstdio>

int add_one(int x) { 
    return x+1;
}

int running_total(int num) {
  static int x = 0;    
  x = x + num;
  return x;
}

void reverse_in_place(int arr[], int len) {
    int i, arrayIndex, revIndex;
    int temp;
    arrayIndex = len - 1;
    revIndex = 0;
    while(revIndex < arrayIndex)
    {
        /* Copy value from orig array to new array */
        temp = arr[revIndex];
        arr[revIndex] = arr[arrayIndex];
        arr[arrayIndex] = temp;
        //increment and de-increment
        arrayIndex--;
        revIndex++;
    }

}

int *reverse(int arr[], int size) {
    int * a = (int *) calloc(size,sizeof(int));
    if(!a)
        return NULL;

    int i, revIndex, arrayIndex;
    int temp;
    revIndex = 0;
    arrayIndex = size - 1;
    while(arrayIndex >= 0)
    {
        /* Copy value from original array to reverse array */
        a[revIndex] = arr[arrayIndex];
        //increment and de-increment
        arrayIndex--;
        revIndex++;
    }
    return a;
}

    int num_instances(int arr[], int len, int val) {
        int instances = 0;
        int arrIndex = len - 1;

        while(arrIndex >= 0)
        {
            //keep count of instances if appears
            if (arr[arrIndex] == val){
                instances++;
            }

            arrIndex--;
        }
        return instances;
}

Point negate(Point p) {
    Point points = { -p.x, -p.y, -p.z };
    return points;
    }  


//returns a newly allocated array whose values are the values of the 
//function argument applied to the array argument
Point *map(Point arr[], int len, Point (*f) (Point)) {
    Point * points = (Point *) calloc(len,sizeof(Point));

    for(int i = 0; i < len; i++){
        points[i] = f(arr[i]);
    }

    return points;
}
