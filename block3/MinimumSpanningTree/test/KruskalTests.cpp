//
// Created by moonlightnvkz on 18.02.17.
//
#include <fstream>
#include <gtest/gtest.h>
#include "../src/MST.h"

using namespace std;

using Param_t = tuple<const char *, double, double>;

class KruskalTest : public testing::TestWithParam<Param_t> {
public:
    virtual void SetUp() override {
        const char *file = get<0>(GetParam());
        double expected_weight = get<1>(GetParam());
        double error = get<2>(GetParam());

        ifstream in(file);
        assert(in.is_open());
        read_input(in);

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
    void read_input(ifstream &in) {
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

double Error = 1E-6;
Param_t params[] = {
        make_tuple("test/test1",  109,      Error),
        make_tuple("test/test2",  12,       Error),
        make_tuple("test/test3",  17,       Error),
        make_tuple("test/test4",  5610,     Error),
        make_tuple("test/test5",  17,       Error),
        make_tuple("test/test6",  2,        Error),
        make_tuple("test/test7",  307,      Error),
        make_tuple("test/test8",  641,      Error),
        make_tuple("test/test9",  672,      Error),
        make_tuple("test/test10", 618,      Error),
        make_tuple("test/test11", 46168182, Error),
        make_tuple("test/test12", 1.81,     Error),
        make_tuple("test/test13", 10.46351, Error),
        make_tuple("test/test14", 20.77320, Error),
        make_tuple("test/test_empty", 0,    Error)
};

TEST_P(KruskalTest, Test) {
    double expected_weight = get<1>(GetParam());
    double error = get<2>(GetParam());
    EXPECT_NEAR(weight, expected_weight, error);
}

INSTANTIATE_TEST_CASE_P(KruskalTest, KruskalTest, testing::ValuesIn(params));