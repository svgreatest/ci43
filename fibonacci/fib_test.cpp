#include "fib.h"
#include <gtest/gtest.h>

TEST(fibonacci, fib_basic) {
    Fibonacci fib;
    fib.fibVector.resize(11);
    fib.fib_rec(10);
    EXPECT_EQ(fib.fibVector[10], 55);
}

TEST(fibonacci, fib_memo) {
    Fibonacci fib;
    fib.fibVector.resize(11, -1);
    fib.fibVector[0] = 0;
    fib.fibVector[1] = 1;
    fib.fib_memo(10);
    EXPECT_EQ(fib.fibVector[10], 55);
}

TEST(fibonacci, fib_dp) {
    Fibonacci fib;
    fib.fibVector.resize(11, -1);
    fib.fibVector[0] = 0;
    fib.fibVector[1] = 1;
    fib.fib_dp(10);
    EXPECT_EQ(fib.fibVector[10], 55);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}