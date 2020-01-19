#include "solutions.h"
#include <cstdio>

int add_one(int x) { 
    return x+1;
}

int running_total(int num) {
  static int x = 0; /* note: must be a literal constant,
                      *  not a computed value */
        
  x = x + num;
  return x;
}

void reverse_in_place(int arr[], int size) {
    int i, arrIndex, revIndex;
    int temp;
    revIndex = 0;
    arrIndex = size - 1;
    while(revIndex < arrIndex)
    {
        /* Copy value from original array to reverse array */
        temp = arr[revIndex];
        arr[revIndex] = arr[arrIndex];
        arr[arrIndex] = temp;
        
        revIndex++;
        arrIndex--;
    }

}

int *reverse(int arr[], int size) {
    int * a = (int *) calloc(size,sizeof(int));
    if(!a)
        return NULL;

    int i, arrIndex, revIndex;
    int temp;
    revIndex = 0;
    arrIndex = size - 1;
    while(arrIndex >= 0)
    {
        /* Copy value from original array to reverse array */
        a[revIndex] = arr[arrIndex];
        
        revIndex++;
        arrIndex--;
    }
    return a;
}

    int num_instances(int arr[], int len, int val) {
        int instances = 0;
        int arrIndex = len - 1;

        while(arrIndex >= 0)
        {
            if (arr[arrIndex] == val){
                instances++;
            }

            arrIndex--;
        }
        return instances;
}

Point negate(Point p) {
    Point points = { -p.x, -p.y, -p.z };
    //printf("negate:\npoints = %lf\n", points.x);
    //printf("points = %lf\n", points.y);
    //printf("points = %lf\n", points.z);

    return points;
    }  


Point *map(Point arr[], int len, Point (*f) (Point)) {
    Point * points = (Point *) calloc(len,sizeof(Point));

    for(int i = 0; i < len; i++){
        points[i] = f(arr[i]);
    }

    return points;
}
