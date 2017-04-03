//
// Created by moonlightnvkz on 25.03.17.
//
#include <random>
#include <regex>
#include <gtest/gtest.h>
#include "../src/DiffRadixPlus.h"
#include "../src/RadixTranslation.h"

using namespace DiffRadixPlus;
using std::make_tuple;


using Param_t_read = std::tuple<const LongNumber, const int,
        const LongNumber, const int, const int>;

class DiffRadixPlus_read_test : public testing::TestWithParam<Param_t_read> {
public:
    virtual void SetUp() override {
        const Param_t_read &param = GetParam();
        LongNumber exp_A = std::get<0>(param);
        int exp_baseA = std::get<1>(param);
        LongNumber exp_B = std::get<2>(param);
        int exp_baseB = std::get<3>(param);
        int exp_baseResult = std::get<4>(param);

        for (const auto &N : {std::make_pair(&exp_A, &exp_baseA), std::make_pair(&exp_B, &exp_baseB)}) {
            ss << *N.second << ": \"";
            for (size_t i = 0; i < N.first->size(); ++i) {
                int digit = N.first->at(i);
                if (digit > 9) {
                    ss << char(digit + 'A' - 10);
                } else {
                    ss << digit;
                }
            }
            ss << "\"" << std::endl;
        }
        ss << exp_baseResult;
    }

    virtual void TearDown() override {
        A = {};
        B = {};
        baseA = baseB = baseResult = 0;
    }

    std::stringstream ss;

    LongNumber A;

    unsigned baseA;

    LongNumber B;

    unsigned baseB;

    unsigned baseResult;
};

using Param_t_write = std::tuple<const LongNumber, const unsigned>;

class DiffRadixPlus_write_test : public testing::TestWithParam<Param_t_write> {
public:
    virtual void SetUp() override {
        const Param_t_write &param = GetParam();
        const LongNumber &ln = std::get<0>(param);
        const unsigned base = std::get<1>(param);
        DiffRadixPlus::write(os, ln, base);
    }

    virtual void TearDown() override {
        os.str("");
    }

    std::stringstream os;
};

using Param_t_plus = std::tuple<const LongNumber, const unsigned,
                                const LongNumber, const unsigned,
                                const LongNumber, const unsigned>;

class DiffRadixPlus_plus_test : public testing::TestWithParam<Param_t_plus> {
public:
    virtual void SetUp() override { }

    virtual void TearDown() override { }
};

std::vector<Param_t_read> generate_params_read() {
    constexpr unsigned long  Seed = 18471957190;
    constexpr unsigned TestsAmount = 40;
    std::mt19937 mt(Seed);
    std::uniform_int_distribution<int> gen(-10, 35);

    std::vector<Param_t_read> params;
    for (unsigned i = 0; i < TestsAmount; ++i) {
        params.push_back({});
        for (unsigned j = 0; j < 2; ++j) {  // we need 2 pairs LongNumber - base
            const size_t size = size_t(std::abs(gen(mt)));
            LongNumber ln;
            for (size_t s = 0; s < size; ++s) {
                int digit = gen(mt);
                ln.push_back(digit);
            }

            int base = gen(mt);
            switch (j) {
                case 0:
                    const_cast<LongNumber&>(std::get<0>(params.back())) = ln;
                    const_cast<int&>(std::get<1>(params.back())) = base;
                default:
                    const_cast<LongNumber&>(std::get<2>(params.back())) = ln;
                    const_cast<int&>(std::get<3>(params.back())) = base;
            }
        }
        const_cast<int&>(std::get<4>(params.back())) = gen(mt);

    }
    return params;
}

TEST_P(DiffRadixPlus_read_test, Read_Test) {
    const Param_t_read &param = GetParam();
    LongNumber exp_A = std::get<0>(param);
    int exp_baseA = std::get<1>(param);
    LongNumber exp_B = std::get<2>(param);
    int exp_baseB = std::get<3>(param);
    int exp_baseResult = std::get<4>(param);

    bool exp_fail = false;
    if (exp_baseA < 0 || exp_baseB < 0 || exp_baseResult < 0) {
        exp_fail = true;
    }
    for (const auto &i : exp_A) {
        if (i < 0) {
            exp_fail = true;
        }
    }
    for (const auto &i : exp_B) {
        if (i < 0) {
            exp_fail = true;
        }
    }
    if (exp_fail) {
        EXPECT_FALSE(DiffRadixPlus::read(ss, A, baseA, B, baseB, baseResult)) << "read fail";
        return;
    } else {
        EXPECT_TRUE(DiffRadixPlus::read(ss, A, baseA, B, baseB, baseResult));
    }

    EXPECT_EQ(A, exp_A);
    EXPECT_EQ(baseA, exp_baseA);
    EXPECT_EQ(B, exp_B);
    EXPECT_EQ(baseB, exp_baseB);
    EXPECT_EQ(baseResult, exp_baseResult);
}

INSTANTIATE_TEST_CASE_P(DiffRadixPlus_read_test, DiffRadixPlus_read_test,
                        testing::ValuesIn(generate_params_read()));


std::vector<Param_t_write> generate_params_write() {
    constexpr unsigned long  Seed = 18471957190;
    constexpr unsigned TestsAmount = 40;
    std::mt19937 mt(Seed);
    std::uniform_int_distribution<int> gen(-10, 40);

    std::vector<Param_t_write> params;
    for (unsigned i = 0; i < TestsAmount; ++i) {
        size_t size = size_t(std::abs(gen(mt)));
        LongNumber ln;
        for (size_t s = 0; s < size; ++s) {
            int digit = gen(mt);
            ln.push_back(digit);
        }
        unsigned base = unsigned(std::abs(gen(mt)));
        params.push_back(std::make_tuple(ln, base));
    }
    return params;
}

TEST_P(DiffRadixPlus_write_test, Write_Test) {
    using sreg_iter = std::sregex_token_iterator;
    std::regex re("(\\s*:\\s*)");   // ": "
    std::regex re_digits("\\s*,\\s*");

    std::string line;
    std::getline(os, line);
    std::vector<std::string> regex_res = {
            sreg_iter(line.begin(), line.end(), re, -1), sreg_iter()
    };
    const Param_t_write &param = GetParam();
    const LongNumber &ln = std::get<0>(param);
    const unsigned base = std::get<1>(param);
    int base_res = -1;
    ASSERT_NO_THROW(base_res = std::stoi(regex_res[0]));
    EXPECT_EQ(base_res, base);
    EXPECT_GT(regex_res.size(), 1) << "Output differs from the template";

    ASSERT_NO_THROW(EXPECT_EQ(base, std::stoi(regex_res[0]))) << "Written base is not a number";

    if (regex_res[1].at(0) == '"') {
        EXPECT_TRUE(regex_res[1].back() == '"');

        size_t ln_size = ln.size();
        ASSERT_EQ(regex_res[1].size() - 2, ln_size);
        for (size_t i = 0; i < ln_size; ++i) {
            if (std::isupper(regex_res[1][i])) {
                EXPECT_EQ(ln[i], regex_res[1][i] - 'A' + 10);
            } else if (std::isdigit(regex_res[1][i])) {
                EXPECT_EQ(ln[i], regex_res[1][i] - '0');
            } else {
                FAIL() << "Symbol is neither upper nor digit " << regex_res[1] << " " << base;
            }
        }
    } else {
        std::vector<std::string> digits{
                sreg_iter(regex_res[1].begin(), regex_res[1].end(), re_digits, -1), sreg_iter()
        };
        size_t digits_size = digits.size();
        ASSERT_EQ(digits_size, ln.size());
        for (size_t i = 0; i < digits_size; ++i) {
                int digit = 0;
                ASSERT_NO_THROW(digit = std::stoi(digits[i]));
                EXPECT_EQ(digit, ln[i]);
        }
    }
}

INSTANTIATE_TEST_CASE_P(DiffRadixPlus_write_test, DiffRadixPlus_write_test,
                        testing::ValuesIn(generate_params_write()));

std::vector<Param_t_plus> generate_params_plus() {
    constexpr unsigned long  Seed = 18471957190;
    constexpr unsigned TestsAmount = 40;
    std::mt19937 mt(Seed);
    std::uniform_int_distribution<unsigned> gen(0, 100);

    std::vector<Param_t_plus> params;
    for (unsigned i = 0; i < TestsAmount; ++i) {
        params.push_back({});
        std::vector<int> num{0, 0, 0};
        for (unsigned j = 0; j < 3; ++j) {
            int &number = num.at(j);
            if (j != 2) {
                number = gen(mt);
                num.at(2) += number;
            }
            LongNumber ln;

            const unsigned base = gen(mt) + 2;

            do {
                int digit = number % 10;
                ln.push_back(digit);
                number /= 10;
            } while (number > 0);
            std::reverse(ln.begin(), ln.end());

            ln = RadixTranslation::translate_from_dec(ln, base);

            switch (j) {
                case 0:
                    const_cast<LongNumber &>(std::get<0>(params.back())) = ln;
                    const_cast<unsigned &>(std::get<1>(params.back())) = base;
                case 1:
                    const_cast<LongNumber &>(std::get<2>(params.back())) = ln;
                    const_cast<unsigned &>(std::get<3>(params.back())) = base;
                default:
                    const_cast<LongNumber &>(std::get<4>(params.back())) = ln;
                    const_cast<unsigned &>(std::get<5>(params.back())) = base;
            }
        }
    }
    return params;
}

TEST_P(DiffRadixPlus_plus_test, Plus_test) {
    const Param_t_plus &params = GetParam();
    const LongNumber &A = std::get<0>(params);
    const unsigned baseA = std::get<1>(params);
    const LongNumber &B = std::get<2>(params);
    const unsigned baseB = std::get<3>(params);
    const LongNumber &expected = std::get<4>(params);
    const unsigned baseResult = std::get<5>(params);

    LongNumber res = DiffRadixPlus::my_plus(A, baseA, B, baseB, baseResult);
    EXPECT_EQ(expected, res) << "In base " << baseResult;
}

INSTANTIATE_TEST_CASE_P(DiffRadixPlus_plus_test, DiffRadixPlus_plus_test,
                        testing::ValuesIn(generate_params_plus()));