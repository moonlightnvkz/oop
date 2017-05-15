//
// Created by moonlightnvkz on 22.04.17.
//

#include <sstream>
#include <istream>
#include <gtest/gtest.h>
#include "../src/ArgumentsParser.h"

using Param_t = std::vector<std::pair<Key, Values>>;

static void print_pair(std::stringstream &is, const std::pair<Key, Values> &p) {
    is << p.first << ' ';
    for (const auto &v : p.second) {
        is << v << ' ';
    }
}

class ArgumentsParserTest : public testing::TestWithParam<Param_t> {
public:
    virtual void SetUp() override {
        for(const auto &p : GetParam()) {
            print_pair(ss, p);
        }
    }

    virtual void TearDown() override {
        ss.str("");
    }
    std::stringstream ss;
};

static void verify(Param_t res, Param_t expected) {
    ASSERT_EQ(res.size(), expected.size());
    size_t size = res.size();
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(res[i].first, expected[i].first);
        ASSERT_EQ(res[i].second.size(), expected[i].second.size());
        size_t values_count = res[i].second.size();
        for (size_t j = 0; j < values_count; ++j) {
            EXPECT_EQ(res[i].second[j], expected[i].second[j]);
        }
    }
}

TEST_P(ArgumentsParserTest, ArgumentParserTest_Positive_Test) {
    std::vector<Key> keys;
    const auto &param = GetParam();
    for(const auto &p : param) {
        keys.push_back(p.first);
    }
    ArgumentsParser parser(keys);
    const auto res = parser.parse(ss);
    verify(res, param);
}

Param_t params_pos[] = {
        {{"k", {"v1"}}},
        {{"k1", {"v11", "v12"}}, {"k2", {"v21", "v22"}}},
        {{"k1", {"v11", "v12"}}, {"k2", {}}},
        {{"k1", {}}, {"k2", {}}},
        {{"k1", {}}, {"k2", {"v21", "v22"}}},
        {{"--k1", {"-k1", "k1"}}, {"k2", {"-k2"}}, {"k2", {"v1"}}}
};

INSTANTIATE_TEST_CASE_P(ArgumentParserTest_Positive_Test, ArgumentsParserTest,
                        testing::ValuesIn(params_pos));

TEST(ArgumentsParserTest, ArgumentParserTest_With_Garbage_Test) {
    std::stringstream ss;
    ArgumentsParser parser{"key1", "key2", "key3"};
    ss << "notkey notkeytoo key v key1 v1 v2 v3 key2 u1 u2 key3 key1";
    const Param_t res = parser.parse(ss);
    Param_t expected{{"key1", {"v1", "v2", "v3"}}, {"key2", {"u1", "u2"}}, {"key3", {}}, {"key1", {}}};
    verify(res, expected);
}

TEST(ArgumentsParserTest, ArgumentParserTest_Only_Garbage_Test) {
    std::stringstream ss;
    ArgumentsParser parser{"-key1", "-key2", "-key3"};
    ss << "notkey notkeytoo key v key1 v1 v2 v3 key2 u1 u2 key3 key1";
    const Param_t res = parser.parse(ss);
    Param_t expected{};
    verify(res, expected);
}