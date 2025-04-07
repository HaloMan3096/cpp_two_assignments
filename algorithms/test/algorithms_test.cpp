#include <gtest/gtest.h>
#include <algorithm>

#include "../include/algo.hpp"

// Demonstrate some basic assertions.
TEST(THOUSAND_DIGIT_TEST, BasicAssertions) {
    const auto val = run();
    // Expect equality.
    EXPECT_EQ(*val, "2143289344");
}

