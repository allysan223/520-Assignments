#ifndef SOLUTIONS_H
#define SOLUTIONS_H

#include <stdlib.h>

 typedef struct {
   double x, y, z;
 } Point;

int add_one(int x);
int running_total(int x);
void reverse_in_place(int arr[], int len);
int *reverse(int arr[], int size);
int num_instances(int arr[], int len, int val);

Point negate(Point p);
Point *map(Point arr[], int size, Point (*f) (Point));

#endif