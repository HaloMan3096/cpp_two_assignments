#include <gtest/gtest.h>
#include <algo.hpp>

// Demonstrate some basic assertions.
TEST(THOUSAND_DIGIT_TEST, BasicAssertions) {
    const auto res = run();
    std::cout << res << std::endl;
    // Expect equality.
    EXPECT_EQ(1, 1);

    EXPECT_EQ(res, "");
}
