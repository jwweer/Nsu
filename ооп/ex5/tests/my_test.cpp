#include "hypotenuse.h"
#include "hypotenuse_rand.h"
#include <gtest/gtest.h>

TEST(HypotenuseSuite, TestNormal) {
    EXPECT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(3, 4), 5.0);
    EXPECT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(6, 8), 10.0);
}

TEST(HypotenuseSuite, TestZero) {
    EXPECT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(0, 0), 0.0);
    EXPECT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(0, 5), 5.0);
}

TEST(HypotenuseSuite, AssertVsExpect) {
    EXPECT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(3, 4), 5.0);
    EXPECT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(3, 4), 99.0);
    EXPECT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(3, 4), 5.0);

    ASSERT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(3, 4), 5.0);
    ASSERT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(3, 4), 99.0);
    EXPECT_DOUBLE_EQ(my_lib::usual::hypotenuse<int>(3, 4), 5.0);
}

TEST(HypotenuseRandSuite, TestRange) {
    for (int i = 0; i < 100; ++i) {
        double v = my_lib::randver::hypotenuse_rand<int>(3, 4);
        EXPECT_GE(v, 5.0);
        EXPECT_LE(v, 15.0);
    }
}