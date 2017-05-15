//
// Created by moonlightnvkz on 25.04.17.
//

#include <gtest/gtest.h>
#include <functional>
#include "../src/Timestamp.h"

using ReadWriteParam_t = std::pair<Timestamp, const char*>;

ReadWriteParam_t readWriteParams[] = {
        {{2005, 8, 9, 18, 31, 42},   "2005-08-09T18:31:42"},
        {{2005, 12, 11, 18, 31, 42}, "2005-12-11T18:31:42"},
        {{205, 8, 9, 18, 31, 42},     "205-08-09T18:31:42"},
        {{2005, 8, 9, 18, 1, 2},     "2005-08-09T18:01:02"},
        {{2005, 8, 9, 18, 0, 0},     "2005-08-09T18:00:00"},
        {{0, 0, 0, 0, 0, 0},            "0-00-00T00:00:00"}
};

class TimestampWriteTest : public testing::TestWithParam<ReadWriteParam_t> {
public:
    virtual void SetUp() { ss << GetParam().first; }

    virtual void TearDown() { ss.str(""); }

    std::stringstream ss;
};

TEST_P(TimestampWriteTest, TimestampWriteTest_Tim_Test) {
    EXPECT_EQ(ss.str(), GetParam().second);
}
INSTANTIATE_TEST_CASE_P(TimestampWriteTest, TimestampWriteTest, testing::ValuesIn(readWriteParams));



class TimestampReadTest : public testing::TestWithParam<ReadWriteParam_t> {
public:
    virtual void SetUp() { ss << GetParam().first; }

    virtual void TearDown() { ss.str(""); }

    std::stringstream ss;
};

TEST_P(TimestampReadTest, TimestampReadTest_Tim_Test) {
    Timestamp ts;
    ss >> ts;
    EXPECT_EQ(ts, GetParam().first);
}
INSTANTIATE_TEST_CASE_P(TimestampReadTest, TimestampReadTest, testing::ValuesIn(readWriteParams));



class TimestampToStringTest : public testing::TestWithParam<ReadWriteParam_t> {
public:
    virtual void SetUp() { str = static_cast<std::string>(GetParam().first); }

    virtual void TearDown() { str.clear(); }

    std::string str;
};

TEST_P(TimestampToStringTest, TimestampToStringTest_T_Test) {
    EXPECT_EQ(str, GetParam().second);
}
INSTANTIATE_TEST_CASE_P(TimestampToStringTest, TimestampToStringTest, testing::ValuesIn(readWriteParams));



using CompareParam_t = std::tuple<Timestamp, Timestamp,
        std::function<bool(const Timestamp&, const Timestamp&)>, bool>;

class TimestampOperatorCompareTest : public testing::TestWithParam<CompareParam_t > {
public:
    virtual void SetUp() {}

    virtual void TearDown() {}
};

using Ts = Timestamp;
CompareParam_t operatorCompareParams[] = {
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 0}, std::equal_to<Ts>(), true),
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 1}, std::equal_to<Ts>(), false),
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 0}, std::less<Ts>(), false),
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 1}, std::less<Ts>(), true),
        std::make_tuple(Ts{0, 0, 0, 0, 1, 0}, Ts{0, 0, 0, 0, 0, 1}, std::less<Ts>(), false),
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 0}, std::less_equal<Ts>(), true),
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 1}, std::less_equal<Ts>(), true),
        std::make_tuple(Ts{0, 0, 0, 0, 1, 0}, Ts{0, 0, 0, 0, 0, 1}, std::less_equal<Ts>(), false),
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 0}, std::greater<Ts>(), false),
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 1}, std::greater<Ts>(), false),
        std::make_tuple(Ts{0, 0, 0, 0, 1, 0}, Ts{0, 0, 0, 0, 0, 1}, std::greater<Ts>(), true),
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 0}, std::greater_equal<Ts>(), true),
        std::make_tuple(Ts{0, 0, 0, 0, 0, 0}, Ts{0, 0, 0, 0, 0, 1}, std::greater_equal<Ts>(), false),
        std::make_tuple(Ts{0, 0, 0, 0, 1, 0}, Ts{0, 0, 0, 0, 0, 1}, std::greater_equal<Ts>(), true)
};

TEST_P(TimestampOperatorCompareTest, TimestampOperatorCompareTest) {
    const CompareParam_t &param = GetParam();
    EXPECT_EQ(std::get<2>(param)(std::get<0>(param), std::get<1>(param)), std::get<3>(param));
}
INSTANTIATE_TEST_CASE_P(TimestampOperatorCompareTest, TimestampOperatorCompareTest,
                        testing::ValuesIn(operatorCompareParams));