//
// Created by moonlightnvkz on 29.04.17.
//


#include <sstream>
#include <gtest/gtest.h>
#include "../src/User.h"
#include "../src/VisitsListReader.h"

class VisitsListReaderTest : public testing::TestWithParam<std::vector<User>> {
public:
    virtual void SetUp() override {
        for (const auto &user : GetParam()) {
            ss << user.startTs() << " - "
               << user.endTs() << " "
               << user.id() << " "
               << user.location()
               << std::endl;
        }
    }

    virtual void TearDown() override {
        ss.str("");
    }

    std::stringstream ss;
};

static User generate_random_user() {
    constexpr const unsigned Seed = 1448419841;
    constexpr const size_t MaxLocLength = 10;
    static std::mt19937 mt(Seed);
    static std::uniform_int_distribution<unsigned> gen(0, 5000);

    Timestamp startTs, endTs;
    unsigned user_id;
    std::string location;
    startTs.years = gen(mt);
    startTs.months = gen(mt);
    startTs.days = gen(mt);
    startTs.hours = gen(mt);
    startTs.minutes = gen(mt);
    startTs.seconds = gen(mt);

    endTs.years = gen(mt);
    endTs.months = gen(mt);
    endTs.days = gen(mt);
    endTs.hours = gen(mt);
    endTs.minutes = gen(mt);
    endTs.seconds = gen(mt);

    user_id = gen(mt);

    const size_t loc_length = gen(mt) % MaxLocLength;
    for (size_t i = 0; i < loc_length; ++i) {
        location.push_back(static_cast<char>(32 + gen(mt) % (256 - 32)));   // start from 32 in ascii table
    }
    return User(startTs, endTs, user_id, location);
}

static std::vector<User> generate_random_list(const unsigned amount) {
    std::vector<User> list;
    for (unsigned i = 0; i < amount; ++i) {
        list.push_back(generate_random_user());
    }
    return list;
}

static std::vector<std::vector<User>> generate_random_params(const unsigned amount) {
    constexpr const unsigned Seed = 481948104;
    static std::mt19937 mt(Seed);
    static std::uniform_int_distribution<unsigned> gen(0, 10);

    std::vector<std::vector<User>> params;
    for (unsigned i = 0; i < amount; ++i) {
        params.push_back(generate_random_list(gen(mt)));
    }
    return params;
}

TEST_P(VisitsListReaderTest, VisitsListReaderTest_Visit_Test) {
    std::vector<User> res;
    EXPECT_TRUE(VisitsListReader::read(ss, res));
    const auto &param = GetParam();
    ASSERT_EQ(res.size(), param.size());
    size_t size = res.size();
    for (size_t i = 0; i < size; ++i) {
        const auto &a = res[i];
        const auto &b = param[i];
        EXPECT_EQ(a.startTs(), b.startTs());
        EXPECT_EQ(a.endTs(), b.endTs());
        EXPECT_EQ(a.id(), b.id());
        EXPECT_EQ(a.location(), b.location());
    }
}

constexpr const unsigned ParamsAmount = 20;

INSTANTIATE_TEST_CASE_P(VisitsListReaderTest, VisitsListReaderTest,
                        testing::ValuesIn(generate_random_params(ParamsAmount)));