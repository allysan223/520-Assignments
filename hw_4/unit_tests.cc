#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include "gtest/gtest.h"

namespace {

    TEST(TypedArray, Construction) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        b.set(20, Point(3,4,5));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).y, 3);
        EXPECT_EQ(b.get(20).z, 5);
    }

    TEST(TypedArray, Pop) {
        TypedArray<Point> b;
        b.set(0, Point(1,2,3));
        b.set(1, Point(2,3,4));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.pop().x, 2);
        EXPECT_EQ(b.size(), 1);

    }

    TEST(TypedArray, Pop2) {
        TypedArray<int> b;
        b.set(0, 5);
        b.set(1, -9);
        EXPECT_EQ(b.get(0), 5);
        EXPECT_EQ(b.pop(), -9);
        EXPECT_EQ(b.pop(), 5);
        ASSERT_THROW(b.pop(), std::range_error);

    }

    TEST(TypedArray, Pop_front) {
        TypedArray<int> b;
        b.set(0, 5);
        b.set(1, -9);
        b.set(2, 1);
        EXPECT_EQ(b.get(0), 5);
        EXPECT_EQ(b.pop_front(), 5);
        EXPECT_EQ(b.pop(), 1);
        EXPECT_EQ(b.pop_front(), -9);
        ASSERT_THROW(b.pop_front(), std::range_error);

    }

    TEST(TypedArray, Push) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        EXPECT_EQ(b.get(0).x, 1);
        EXPECT_EQ(b.get(1).z, 4);
        EXPECT_EQ(b.size(), 2);

    }


    TEST(TypedArray, Push_front) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push_front(Point(2,3,4));
        EXPECT_EQ(b.get(0).x, 2);
        EXPECT_EQ(b.get(1).z, 3);
        EXPECT_EQ(b.size(), 2);
        b.push(Point(1,2,3));
        b.push_front(Point(2,3,40));
        b.push(Point(1,2,3));
        b.push_front(Point(20,3,4));
        EXPECT_EQ(b.get(0).x, 20);
        EXPECT_EQ(b.get(1).z, 40);
        EXPECT_EQ(b.size(), 6);
        EXPECT_EQ(b.pop().x, 1);
        EXPECT_EQ(b.pop_front().x, 20);


    }


    TEST(TypedArray, Matrix) {

        TypedArray<TypedArray<double>> m;

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                m.get(i).set(j,3*i+j);
            }
        }

        std::cout << m << "\n"; 

        for (int i=0; i<3; i++) {
            for (int j=0; j<3; j++) {
                EXPECT_DOUBLE_EQ(m.get(i).get(j),3*i+j);
            }
        }

    }

    TEST(TypedArray,CopyElementsInSet1) {
        TypedArray<Point> b;
        Point p(1,2,3);
        b.set(0, p);
        p.x = 4;
        EXPECT_DOUBLE_EQ(b.get(0).x, 1);
    }

    TEST(TypedArray,CopyElementsInSet2) {
        TypedArray<TypedArray<double>> m;
        TypedArray<double> x;
        x.set(0,0);
        m.set(0,x);
        x.set(0,-1);
        EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                               // then we would expect m[0][0]
                                               // to be x[0], which we changed 
                                               // to -1.
    }    

}