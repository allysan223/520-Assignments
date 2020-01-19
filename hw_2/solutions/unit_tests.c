#include "gtest/gtest.h"
#include "solutions.h"

namespace { 

    TEST(HW2,RunningTotal) {
        ASSERT_EQ(running_total(1),  1);
        ASSERT_EQ(running_total(1),  2);
        ASSERT_EQ(running_total(5),  7);
        ASSERT_EQ(running_total(-3), 4);      
 }

    TEST(HW2,ReverseInPlace) {
        int x[] = {10,20,30,40,60};
        reverse_in_place(x,5);
        ASSERT_EQ(x[0],60);
        ASSERT_EQ(x[1],40);       
        ASSERT_EQ(x[2],30);   
        ASSERT_EQ(x[3],20);   
        ASSERT_EQ(x[4],10);                            
 }   

    TEST(HW2,Reverse) {
        int x[] = {10,20,30,40,50};
        int * y = reverse(x,5);
        ASSERT_EQ(y[0],50);
        ASSERT_EQ(y[1],40);       
        ASSERT_EQ(y[2],30);   
        ASSERT_EQ(y[3],20);   
        ASSERT_EQ(y[4],10);  
        free(y);
 }
    TEST(HW2,NumInstances) {
        int a[] = { 1, 1, 2, 3, 1, 4, 5, 2, 20, 5 };
        ASSERT_EQ(num_instances(a,10,1), 3);
        ASSERT_EQ(num_instances(a,10,20), 1);
        ASSERT_EQ(num_instances(a,10,13), 0);
 }

    TEST(HW2,PointMap) {
        Point a[] = { { 1,2,3 }, { 2,3,4 } };
        Point * b = map(a,2,negate);
        for(int i=0; i<2; i++) {
            ASSERT_EQ(b[0].z,-3);
            ASSERT_EQ(b[1].z,-4);
            ASSERT_EQ(b[i].x,-a[i].x);
            ASSERT_EQ(b[i].y,-a[i].y);
            ASSERT_EQ(b[i].z,-a[i].z);
        }
        free(b);

    }
}
