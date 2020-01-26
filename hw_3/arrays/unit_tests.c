#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include "dynamic_array.h"
#include "gtest/gtest.h"

#define X 1.2345

namespace {

    TEST(DynamicArray, CreateAndDestroy) {
        DynamicArray * a = DynamicArray_new();
        DynamicArray_destroy(a);
    }

    TEST(DynamicArray, DeathTests) {
        DynamicArray * a = DynamicArray_new();
        ASSERT_DEATH(DynamicArray_pop(a), ".*Assertion.*");
        ASSERT_DEATH(DynamicArray_pop_front(a), ".*Assertion.*");
        DynamicArray_destroy(a);
        ASSERT_DEATH(DynamicArray_size(a), ".*Assertion.*");
    }    

    TEST(DynamicArray, SmallIndex) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_set(da, 0, -X);        
        DynamicArray_set(da, 3, X);
        ASSERT_EQ(DynamicArray_size(da),4);
        ASSERT_EQ(DynamicArray_get(da,0), -X);
        ASSERT_EQ(DynamicArray_get(da,3), X);
        DynamicArray_destroy(da);
    }

    TEST(DynamicArray, BigIndex) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 8, X);
        ASSERT_EQ(DynamicArray_get(da,8), X);
        DynamicArray_destroy(da);              
    }

    TEST(DynamicArray, ReallyBig) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_set(da, 400, X);
        DynamicArray_set(da, 200, X/2);        
        ASSERT_EQ(DynamicArray_get(da,200), X/2);
        ASSERT_EQ(DynamicArray_get(da,400), X);
        DynamicArray_destroy(da);              
    }  

    TEST(DynamicArray, Push) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        printf("Push test Intermediate Result: %s\n", 
               DynamicArray_to_string(da));
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, PushFront) {
        DynamicArray * da = DynamicArray_new();
        double x = 0;
        while ( x < 10 ) {
            DynamicArray_push_front(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_size(da),40);
        while ( DynamicArray_size(da) > 0 ) {
            DynamicArray_pop_front(da);
        }
        ASSERT_EQ(DynamicArray_size(da),0);
        DynamicArray_destroy(da);          
    } 

    TEST(DynamnicArray,ToString) {
        DynamicArray * da = DynamicArray_new();
        double x = 1.0;
        while ( x <= 5 ) {
            DynamicArray_push(da, x);  
            x += 1.0;
        }
        char * str = DynamicArray_to_string(da);
        printf("ToString Example: %s\n", str);
        ASSERT_STREQ(
            str,
            "[1.00000,2.00000,3.00000,4.00000,5.00000]"
        );
        DynamicArray_destroy(da);
        free(str);
    }

    TEST(DynamicArray, Pop) {
        DynamicArray * da = DynamicArray_new();
        double x;
        DynamicArray_push(da, X);  
        DynamicArray_push(da, X);  
        x = DynamicArray_pop(da);  
        ASSERT_EQ(DynamicArray_size(da),1);
        ASSERT_EQ(x,X);
        ASSERT_EQ(DynamicArray_get(da,1), 0.0);
        DynamicArray_destroy(da);          
    }

    TEST(DynamicArray, Map) {
        DynamicArray * t = DynamicArray_new(),
                     * y;
        double s = 0.0;
        for ( int i=0; i<628; i++ ) {
            DynamicArray_set(t, i, s);
            s = s + 0.1;
        }
        y = DynamicArray_map(t,sin);
        for (int i=0; i<DynamicArray_size(t); i++) {
            ASSERT_NEAR(
                DynamicArray_get(y,i),sin(0.1*i), 0.0001
            );
        }
        DynamicArray_destroy(t);    
        DynamicArray_destroy(y);                    
    }   

    /*! Mathematical operations */
    TEST(DynamicArray, Min) {
        DynamicArray * da = DynamicArray_new();
        double x = 5.0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_min(da),5.0);
        DynamicArray_destroy(da);   

        DynamicArray * da1 = DynamicArray_new();
        //DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da1, 3.0); 
        DynamicArray_push(da1, 5.0);  
        DynamicArray_push(da1, 2.0);
        DynamicArray_push(da1, -5.0);  
        DynamicArray_push(da1, 10.0);   
        printf("MIN test Intermediate Result: %s\n", 
               DynamicArray_to_string(da1)); 

        ASSERT_EQ(DynamicArray_min(da1),-5.0);
        DynamicArray_destroy(da1);   
    }    

    TEST(DynamicArray, Max) {
        DynamicArray * da = DynamicArray_new();
        double x = 5.0;
        while ( x < 10 ) {
            DynamicArray_push(da, x);  
            x += 0.25;
        }
        ASSERT_EQ(DynamicArray_max(da),9.75);
        DynamicArray_destroy(da);   

        DynamicArray * da1 = DynamicArray_new();
        //DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da1, 3.0); 
        DynamicArray_push(da1, 5.0);  
        DynamicArray_push(da1, 12.0);
        DynamicArray_push(da1, -5.0);  
        DynamicArray_push(da1, 10.0);   

        ASSERT_EQ(DynamicArray_max(da1),12.0);
        DynamicArray_destroy(da1);   
    }    

    TEST(DynamicArray, Mean) {
        DynamicArray * da = DynamicArray_new();
        double x = 5.0;
        while ( x < 10 ) {
            DynamicArray_push(da, 1.0);  
            x += 1;
        }
        ASSERT_EQ(DynamicArray_mean(da),1);
        DynamicArray_destroy(da);   

        DynamicArray * da1 = DynamicArray_new();
        //DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da1, 3.0); 
        DynamicArray_push(da1, 5.0);  
        DynamicArray_push(da1, 12.0);
        DynamicArray_push(da1, -5.0);  
        DynamicArray_push(da1, 10.0);   

        ASSERT_EQ(DynamicArray_mean(da1),5.0);
        DynamicArray_destroy(da1);   
    }

    TEST(DynamicArray, Median) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 1.0); 
        DynamicArray_push(da, 3.0);  
        DynamicArray_push(da, 3.0);
        DynamicArray_push(da, 6.0);  
        DynamicArray_push(da, 7.0); 
        DynamicArray_push(da, 8.0); 
        DynamicArray_push(da, 9.0); 
        ASSERT_EQ(DynamicArray_median(da),6);
        DynamicArray_destroy(da);   

        DynamicArray * da1 = DynamicArray_new();
        //DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da1, 1.0); 
        DynamicArray_push(da1, 2.0);  
        DynamicArray_push(da1, 3.0);
        DynamicArray_push(da1, 4.0);  
        DynamicArray_push(da1, 5.0); 
        DynamicArray_push(da1, 6.0);
        DynamicArray_push(da1, 8.0);  
        DynamicArray_push(da1, 9.0);   
        ASSERT_EQ(DynamicArray_median(da1),4.5);
        DynamicArray_destroy(da1);   
    }

    TEST(DynamicArray, Sum) {
        DynamicArray * da = DynamicArray_new();
        ASSERT_EQ(DynamicArray_sum(da),0);
        DynamicArray_destroy(da);   

        DynamicArray * da1 = DynamicArray_new();
        //DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da1, 1.0); 
        DynamicArray_push(da1, 2.0);  
        DynamicArray_push(da1, 3.0);
        DynamicArray_push(da1, -4.0);  
        DynamicArray_push(da1, 5.0); 
        ASSERT_EQ(DynamicArray_sum(da1),7);
        DynamicArray_destroy(da1);   
    }

    TEST(DynamicArray, Copy) {
        DynamicArray * da = DynamicArray_new();
        DynamicArray_push(da, 1.0); 
        DynamicArray_push(da, 3.0);  
        DynamicArray_push(da, 3.0);
        DynamicArray_push(da, 6.0);  
        DynamicArray_push(da, 7.0); 
        DynamicArray_push(da, 8.0); 
        DynamicArray_push(da, 9.0); 

        DynamicArray * da1 = DynamicArray_copy(da);

        ASSERT_EQ(DynamicArray_size(da),DynamicArray_size(da1));

        for (int i=0; i<DynamicArray_size(da); i++) {
            ASSERT_EQ(DynamicArray_get(da,i),DynamicArray_get(da1,i));
        }

        DynamicArray_destroy(da);   
        DynamicArray_destroy(da1);   
    }

    TEST(DynamicArray, Range) {
        DynamicArray * a = DynamicArray_range(0, 1, 0.1); /* yields [ 0, 0.1, 0.2, ..., 1.0 ] */
        ASSERT_EQ(DynamicArray_size(a),11);
        int index = 0;
        for (double i=0; i<= 1; i+= 0.1) {
            ASSERT_EQ(DynamicArray_get(a,index),i);
            index++;
        }

        DynamicArray_destroy(a);   
    }

    TEST(DynamicArray, Concat) {
        DynamicArray * a = DynamicArray_range(2, 3, 1); /* yields [ 0, 0.1, 0.2, ..., 1.0 ] */
        DynamicArray * b = DynamicArray_range(0, 6, .75); 
        printf("Concat B string: %s\n", DynamicArray_to_string(b));       
        DynamicArray * c = DynamicArray_concat(a, b);
        //ASSERT_EQ(DynamicArray_size(a),11);

        printf("Concat string: %s\n", DynamicArray_to_string(c)); 

        DynamicArray_destroy(a);   
        DynamicArray_destroy(b);
        DynamicArray_destroy(c);
    }

}