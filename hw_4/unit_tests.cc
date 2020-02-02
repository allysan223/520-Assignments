#include <math.h>
#include <float.h> /* defines DBL_EPSILON */
#include <assert.h>
#include "typed_array.h"
#include "point.h"
#include "complex.h"
#include "gtest/gtest.h"

namespace {

    TEST(Complex, create) {
        Complex x(1,2), y(3);
    }

    template<typename T>
    int compare(const T& x, const T& y) {
        if ( x < y ) {
            return -1;
        } else if ( y < x ) {
            return 1;
        } else {
            return 0;
        }
    }    

    TEST(Complex,Templates) {
        EXPECT_EQ(compare(1.0, 2.0), -1);
        EXPECT_EQ(compare(Complex(5,4), Complex(-3,4)), 1);
    }

    TEST(Complex,re_imag) {
        Complex x(1,2), y(3);
        EXPECT_EQ(x.real(), 1);
        EXPECT_EQ(x.imag(), 2);
    }

    TEST(Complex,conjugate) {
        Complex x(1,2), y(3);
        y = x.conjugate();
        EXPECT_EQ(x.real(), 1);
        EXPECT_EQ(x.imag(), 2);
        EXPECT_EQ(y.real(), 1);
        EXPECT_EQ(y.imag(), -2);

        Complex z(2,5);
        z.conjugate();
        EXPECT_EQ(z.real(), 2);
        EXPECT_EQ(z.imag(), 5);
        EXPECT_EQ(z.conjugate().imag(), -5);
    }

    TEST(Complex,math) {
        Complex x(4,-3), y(2,5);
        Complex z = y * x;
        Complex z1 = x + y;
        EXPECT_EQ(z.real(),23);
        EXPECT_EQ(z.imag(),14);
        EXPECT_EQ(z1.real(),6);
        EXPECT_EQ(z1.imag(),2);

        Complex a(0, 2), b(-3,0);
        Complex c = a * b;
        EXPECT_EQ(c.real(),0);
        EXPECT_EQ(c.imag(),-6);
        c = a + b + b;
        EXPECT_EQ(c.real(),-6);
        EXPECT_EQ(c.imag(),2);
    }

    TEST(Complex,equals) {
        Complex x(4,-3), y(2,5);
        Complex z(2,5);
        EXPECT_EQ(x == y, false);
        EXPECT_EQ(z == y, true);
        ASSERT_EQ(y, z); 
    }
    

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

    TEST(TypedArray, concat) {
        TypedArray<int> a;
        a.push(2);
        a.push(4);
        TypedArray<int> b;
        b.push(5);
        b.push(6);
        b.push(7);
        TypedArray<int> c = a.concat(b);
        EXPECT_EQ(c.get(0), 2);
        EXPECT_EQ(c.get(1), 4);
        EXPECT_EQ(c.get(2), 5);
        EXPECT_EQ(c.get(4), 7);
        EXPECT_EQ(c.size(), 5);

        TypedArray<int> d = a.concat(b).concat(c);
        EXPECT_EQ(d.size(), 10);
        EXPECT_EQ(d.get(0), 2);
        EXPECT_EQ(d.get(1), 4);
        EXPECT_EQ(d.get(3), 6);
        EXPECT_EQ(d.get(8), 6);


        EXPECT_EQ(a.size(), 2);
    }

    TEST(TypedArray, Reverse) {
        TypedArray<Point> b;
        b.push(Point(1,2,3));
        b.push(Point(2,3,4));
        b.push(Point(6,7,8));
        b = b.reverse();
        EXPECT_EQ(b.get(0).x, 6);
        EXPECT_EQ(b.get(2).z, 3);
        EXPECT_EQ(b.size(), 3);

    }

    TEST(TypedArray, Reverse2) {
        TypedArray<int> b;
        b.push(3);
        b.push(6);
        b.push(1);
        b = b.reverse();
        EXPECT_EQ(b.get(0), 1);
        EXPECT_EQ(b.get(2), 3);
        EXPECT_EQ(b.size(), 3);
        b = b.reverse();
        EXPECT_EQ(b.get(0), 3);
        EXPECT_EQ(b.get(2), 1);
    }

    TEST(TypedArray, Add) {
        TypedArray<int> a;
        a.set(0,0);
        a.set(1,1);
        TypedArray<int> b = a + a + a; // yields [0,1,0,1,0,1]
        EXPECT_EQ(b.get(0), 0);
        EXPECT_EQ(b.get(1), 1);
        EXPECT_EQ(b.get(3), 1);
        EXPECT_EQ(b.get(4), 0);
        EXPECT_EQ(b.size(), 6);

        b = b + b + a;
        EXPECT_EQ(b.size(), 14);
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