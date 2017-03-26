//
// Created by moonlightnvkz on 18.02.17.
//
#include <fstream>
#include <gtest/gtest.h>
#include "../src/MST.h"

using std::make_tuple;
using std::make_pair;
using std::get;

using Param_t = std::tuple<const char *, const double, const double>;

class KruskalTest : public testing::TestWithParam<Param_t> {
public:
    virtual void SetUp() override {
        const char *file = get<0>(GetParam());

        std::ifstream in(file);
        assert(in.is_open());
        read_input(in);

        weight = 0;
        auto mst = build(points_amount, edges);
        for (auto e : mst) {
            weight += e.first;
        }
    }

    virtual void TearDown() override {
        edges.clear();
        points_amount = 0;
        weight = 0;
    }
public:
    weighted_edges_array_t edges;
    size_t points_amount;
    double weight;

private:
    void read_input(std::ifstream &in) {
        size_t edges_amount;
        in >> points_amount >> edges_amount;
        for (size_t i = 0; i < edges_amount; ++i) {
            size_t x, y;
            double weight;
            in >> x >> y >> weight;
            edges.push_back(make_pair(weight, make_pair(x, y)));
        }
    }
};

const double Error = 1E-6;
Param_t params[] = {
        make_tuple("test/test1",  109,      Error),
        make_tuple("test/test2",  12,       Error),
        make_tuple("test/test3",  17,       Error),
        make_tuple("test/test4",  5610,     Error),
        make_tuple("test/test5",  17,       Error),
        make_tuple("test/test6",  2,        Error),
        make_tuple("test/test7",  307,      Error),
        make_tuple("test/test8", 1.81,     Error),
        make_tuple("test/test9", 10.46351, Error),
        make_tuple("test/test10", 20.77320, Error),
        make_tuple("test/test_disconnected1", 0, Error),
        make_tuple("test/test_disconnected2", 0, Error),
        make_tuple("test/test_empty", 0, Error)
};

TEST_P(KruskalTest, Test) {
    const double expected_weight = get<1>(GetParam());
    const double error = get<2>(GetParam());
    EXPECT_NEAR(weight, expected_weight, error) << get<0>(GetParam());
}

INSTANTIATE_TEST_CASE_P(KruskalTest, KruskalTest, testing::ValuesIn(params));