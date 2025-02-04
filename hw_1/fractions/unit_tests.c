#include "fraction.h"
#include "gtest/gtest.h"

namespace {

    TEST(Fractions, Basics) {
        Fraction a = (Fraction) { 2, 3 },
                 b = (Fraction) { 4, 5 };
        EXPECT_EQ(add(a,b).num,22);
        EXPECT_EQ(add(a,b).den,15);
        EXPECT_EQ(multiply(a,b).num,8);
        EXPECT_EQ(multiply(a,b).den,15);

        a = (Fraction) { -21, 33 };
        EXPECT_EQ(reduce(a).num,-7);
        EXPECT_EQ(reduce(a).den,11);

        a = (Fraction) { 8, 4 };
        EXPECT_EQ(reduce(a).num,2);
        EXPECT_EQ(reduce(a).den,1);

        a = (Fraction) { -12, -16 };
        EXPECT_EQ(reduce(a).num,3);
        EXPECT_EQ(reduce(a).den,4);

        a = (Fraction) { 0, 33 };
        EXPECT_EQ(reduce(a).num,0);
        EXPECT_EQ(reduce(a).den,33);

        a = (Fraction) { 50, 100 };
        EXPECT_EQ(reduce(a).num,1);
        EXPECT_EQ(reduce(a).den,2);

        a = (Fraction) { 50, 0 };
        EXPECT_EQ(reduce(a).num,1);
        EXPECT_EQ(reduce(a).den,0);
    }

}
