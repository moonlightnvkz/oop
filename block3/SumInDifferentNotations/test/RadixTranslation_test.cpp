//
// Created by moonlightnvkz on 18.02.17.
//
#include <gtest/gtest.h>
#include "../src/RadixTranslation.h"

using namespace std;

class RadixTranslation_test : public testing::TestWithParam<tuple<LongNumber, unsigned, LongNumber>> {
public:
    LongNumber res;
};

class Translation_to_Dec_test : public RadixTranslation_test {
public:
    virtual void SetUp() override {
        res = translate_to_dec(get<0>(GetParam()), get<1>(GetParam()));
    }

    virtual void TearDown() override {

    }
};

class Translation_from_Dec_test : public RadixTranslation_test {
public:
    virtual void SetUp() override {
        res = translate_from_dec(get<0>(GetParam()), get<1>(GetParam()));
    }

    virtual void TearDown() override {

    }
};

tuple<LongNumber, unsigned, LongNumber> to_dec_params[] = {
        make_tuple(LongNumber({ 0 }),                     2, LongNumber({ 0 })),
        make_tuple(LongNumber({ 1 }),                     2, LongNumber({ 1 })),
        make_tuple(LongNumber({ 0,1 }),                   2, LongNumber({ 1 })),
        make_tuple(LongNumber({ 1,0 }),                   2, LongNumber({ 2 })),
        make_tuple(LongNumber({ 1,0,0,1,0,1,0,1,0,0,1 }), 2, LongNumber({ 1,1,9,3 })),
        make_tuple(LongNumber({ 0 }),                     3, LongNumber({ 0 })),
        make_tuple(LongNumber({ 1 }),                     3, LongNumber({ 1 })),
        make_tuple(LongNumber({ 0,1 }),                   3, LongNumber({ 1 })),
        make_tuple(LongNumber({ 1,0 }),                   3, LongNumber({ 3 })),
        make_tuple(LongNumber({ 2 }),                     3, LongNumber({ 2 })),
        make_tuple(LongNumber({ 0,2 }),                   3, LongNumber({ 2 })),
        make_tuple(LongNumber({ 2,0,1,2,1,0,2,1 }),       3, LongNumber({ 4,8,1,3 })),
        make_tuple(LongNumber({ 9, 1, 3, 1, 5, 6 }),     10, LongNumber({ 9, 1, 3, 1, 5, 6 }))
};

TEST_P(Translation_to_Dec_test, Test_to_Dec) {
    EXPECT_EQ(res,get<2>(GetParam()));
}

INSTANTIATE_TEST_CASE_P(Translation_to_Dec_test, Translation_to_Dec_test, testing::ValuesIn(to_dec_params));

tuple<LongNumber, unsigned, LongNumber> from_dec_params[] = {
        make_tuple(LongNumber({ 0 }),                     2, LongNumber({ 0 })),
        make_tuple(LongNumber({ 1 }),                     2, LongNumber({ 1 })),
        make_tuple(LongNumber({ 0,1 }),                   2, LongNumber({ 1 })),
        make_tuple(LongNumber({ 2 }),                     2, LongNumber({ 1,0 })),
        make_tuple(LongNumber({ 1,1,9,3 }),               2, LongNumber({ 1,0,0,1,0,1,0,1,0,0,1 })),
        make_tuple(LongNumber({ 0 }),                     3, LongNumber({ 0 })),
        make_tuple(LongNumber({ 1 }),                     3, LongNumber({ 1 })),
        make_tuple(LongNumber({ 0,1 }),                   3, LongNumber({ 1 })),
        make_tuple(LongNumber({ 3 }),                     3, LongNumber({ 1,0 })),
        make_tuple(LongNumber({ 2 }),                     3, LongNumber({ 2 })),
        make_tuple(LongNumber({ 0,2 }),                   3, LongNumber({ 2 })),
        make_tuple(LongNumber({ 4,8,1,3 }),               3, LongNumber({ 2,0,1,2,1,0,2,1 })),
        make_tuple(LongNumber({ 9, 1, 3, 1, 5, 6 }),     10, LongNumber({ 9, 1, 3, 1, 5, 6 }))
};

TEST_P(Translation_from_Dec_test, Translation_from_Dec_test) {
    EXPECT_EQ(res, get<2>(GetParam()));
}

INSTANTIATE_TEST_CASE_P(Translation_from_Dec_test, Translation_from_Dec_test, testing::ValuesIn(from_dec_params));