//
// Created by moonlightnvkz on 03.04.17.
//
#include <vector>
#include <string>
#include <gtest/gtest.h>
#include "../src/TopoSorter.h"

using Param_t = std::pair<std::string, std::vector<std::string>>;

class TopoSorter_test : public testing::TestWithParam<Param_t> {
public:
    virtual void SetUp() override {
        const Param_t &param = GetParam();
        std::vector<std::pair<TopoSorter::Name , TopoSorter::Dependencies >> nodes;

        std::stringstream is(param.first);
        TopoSorter topoSorter(is);

        res = topoSorter.sort();
    }

    virtual void TearDown() override {

    }

    std::vector<std::string> res;
};

TEST_P(TopoSorter_test, TopoSorter_test_T_Test) {
    const Param_t &param = GetParam();
    std::vector<std::string> expected{param.second};
    EXPECT_EQ(expected, res);
}

Param_t params[] = {

        {"1 = 2\n2 = 3", {"1", "2", "3"}},
        {"2 = 1\n3 = 2", {"3", "2", "1"}},
        {"2 = 1\n3 = 2\n1 = ", {"3", "2", "1"}},
        {"2 = 1\n3 = 2\n1 = \n2 = \n3 = ", {"3", "2", "1"}},
        {"2 = 3\n1 = 2\n0 = ", {"1", "2", "3", "0"}},
        {"0 = \n2 = 3\n1 = 2\n0 = ", {"1", "2", "3", "0"}},
        {"0 = \n3 = 2\n3 = 2\n3 = 1\n2 = 1\n0 = \n3 = \n2 = \n1 = ", {"3", "2", "1", "0"}},
        {"0 = \n3 = 2\n3 = 2, 1\n3 = 1\n2 = 1, 1, 1\n0 = \n3 = \n2 = \n1 = ", {"3", "2", "1", "0"}},
        {"1 = 2\n2 = 1", {}},
        {"1 = 2\n2 = 3\n3 = 1", {}},
        {"two = three\nfour = six\none = three\n"
                "two = four\nsix = nine\nfive = seven\n"
                "five = eight\nfive = nine\nseven = eight\n"
                "eight = nine\none = two\nfour = five\n"
                "four = six\nthree = six\nsix = seven\n"
                "three = four", {"one", "two", "three", "four",
                                                  "six", "five", "seven", "eight", "nine"}},
        {"6 = 5\n5 = 4\n4 = 11\n4 = 10\n4 = 12\n12 = 20\n11 = 20\n"
                 "10 = 20\n10 = 22\n11 = 22\n12 = 22\n22 = 21\n21 = 20",
                {"6", "5", "4", "12", "11", "10", "22", "21", "20"}},
        {"6 = 5\n5 = 4\n22 = 21\n21 = 20\n4 = 22\n10 = \n11 = \n12 = ",
                {"6", "5", "4", "22", "21", "20", "12", "11", "10"}},
        {"1", {"1"}},
        {"", {}}

};
INSTANTIATE_TEST_CASE_P(TopoSorter_test, TopoSorter_test, testing::ValuesIn(params));