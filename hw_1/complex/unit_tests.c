#include "complex.h"
#include <math.h>
#include "gtest/gtest.h"

namespace {

    TEST(Complex, Basics) {
        Complex a = (Complex) { 4, -3 },
                 b = (Complex) { 2, 5 };
        EXPECT_EQ(add(a,b).real,6);
        EXPECT_EQ(add(a,b).im,2);
        EXPECT_EQ(multiply(a,b).real,23);
        EXPECT_EQ(multiply(a,b).im,14);
        EXPECT_EQ(negate(a).real,-4);
        EXPECT_EQ(negate(a).im,3);
        EXPECT_EQ(negate(b).real,-2);
        EXPECT_EQ(negate(b).im,-5);
        EXPECT_EQ(magnitude(a),5);
        EXPECT_EQ(magnitude(b),sqrt(29));
    }

}
