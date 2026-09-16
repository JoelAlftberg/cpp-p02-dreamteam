/**
 * @file Test framework usage example.
 */
#include <cmath>

#include "yrgo/test/test.h"

/**
 * @brief Test integer addition.
 *
 *        Add two integers and expect the result to be exact.
 */
TEST(Math, Addition) { EXPECT_EQ(2 + 3, 5); }

/**
 * @brief Test floating-point division.
 *
 *        Divide 1 by 3 and expect the result to be within tolerance.
 */
TEST(Math, FloatingPoint) { EXPECT_NEAR(1.0 / 3.0, 0.333, 1e-3); }

/**
 * @brief Test integer inequality.
 *
 *        Compare two different integers and expect them to be unequal.
 */
TEST(Math, Inequality) { EXPECT_NE(2 + 3, 6); }

/**
 * @brief Test boolean expressions.
 *
 *        Evaluate two boolean expressions and expect true and false respectively.
 */
TEST(Logic, BooleanChecks)
{
    EXPECT_TRUE(10 > 5);
    EXPECT_FALSE(10 < 5);
}

/**
 * @brief Run all test cases.
 *
 * @return 0 on success, or -1 on failure.
 */
int main() { return yrgo::test::runAllTests() ? 0 : -1; }
