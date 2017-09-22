//
// Created by moonlightnvkz on 05.09.17.
//

#include <gtest/gtest.h>
#include "../include/StaticAssert.hpp"

TEST(TestTrue, StaticAssertTest) {
    STATIC_ASSERT<true>("True");
}

TEST(TestFalse, StaticAssertTest) {
    STATIC_ASSERT<false>("False");
}