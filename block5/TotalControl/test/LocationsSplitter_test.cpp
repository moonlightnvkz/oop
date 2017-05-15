//
// Created by moonlightnvkz on 29.04.17.
//

#include <gtest/gtest.h>
#include "../src/LocationsSplitter.h"
#include "../src/Location.h"
#include "../src/User.h"

using Param_t = std::pair<std::vector<User>, std::vector<Location>>;

class LocationsSplitterTest : public testing::TestWithParam<Param_t> {
public:
    virtual void SetUp() override {

    }

    virtual void TearDown() override {
        for (const auto &loc : GetParam().second) {
            for (auto &u : const_cast<std::vector<User*>&>(loc.users())) {
                delete u;
                u = nullptr;
            }
        }
    }
};

TEST_P(LocationsSplitterTest, LocationsSplitterTest_LocationsSpli_Test) {
    const Param_t &param = GetParam();
    std::vector<Location> res = LocationsSplitter::split(param.first);
    ASSERT_EQ(res.size(), param.second.size());
    size_t size = res.size();
    std::sort(res.begin(), res.end(), [](const Location &a, const Location &b) {
        return a.name() < b.name();
    });
    std::sort(const_cast<Param_t&>(param).second.begin(),
              const_cast<Param_t&>(param).second.end(), [](const Location &a, const Location &b) {
        return a.name() < b.name();
    });
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(res[i].name(), param.second[i].name());
        const std::vector<User*> &res_u = res[i].users();
        const std::vector<User*> &param_u = param.second[i].users();

        std::sort(const_cast<std::vector<User*>&>(res_u).begin(),
                  const_cast<std::vector<User*>&>(res_u).end(), [](const User *a, const User *b) {
                    return a->id() < b->id();
        });
        std::sort(const_cast<std::vector<User*>&>(param_u).begin(),
                  const_cast<std::vector<User*>&>(param_u).end(), [](const User *a, const User *b) {
                    return a->id() < b->id();
        });

        ASSERT_EQ(res_u.size(), param_u.size());
        size_t size_u = res_u.size();
        for (size_t j = 0; j < size_u; ++j) {
            ASSERT_FALSE(res_u[j] == nullptr);
            ASSERT_FALSE(param_u[j] == nullptr);
            EXPECT_EQ(*res_u[j], *param_u[j]);
        }
    }
}

static std::string generate_random_loc_name(const size_t length, std::mt19937 &mt,
                                            std::uniform_int_distribution<unsigned> &gen) {
    std::string location;
    for (size_t i = 0; i < length; ++i) {
        location.push_back(static_cast<char>(32 + gen(mt) % (256 - 32)));   // start from 32 in ascii table
    }
    return location;
}

static Timestamp generate_random_timestamp(std::mt19937 &mt,
                                            std::uniform_int_distribution<unsigned> &gen) {
    Timestamp ts;
    ts.years = gen(mt);
    ts.months = gen(mt);
    ts.days = gen(mt);
    ts.hours = gen(mt);
    ts.minutes = gen(mt);
    ts.seconds = gen(mt);
    return ts;
}

static std::vector<Param_t> generate_params(const unsigned amount) {
    constexpr const unsigned Seed = 1448419841;
    constexpr const size_t LocNameLength = 10;
    constexpr const unsigned MaxLocationsAmount = 10;
    constexpr const unsigned MaxUsersAmount = 10;
    static std::mt19937 mt(Seed);
    static std::uniform_int_distribution<unsigned> gen(0, 100);

    std::vector<Param_t> params;
    for (unsigned i = 0; i < amount; ++i) {
        std::vector<User> users;
        std::vector<Location> locations;
        unsigned locations_amount = gen(mt) % MaxLocationsAmount + 1;
        for (unsigned j = 0; j < locations_amount; ++j) {
            std::string loc_name = generate_random_loc_name(LocNameLength, mt, gen);
            std::vector<User*> loc_users;
            unsigned users_amount = gen(mt) % MaxUsersAmount + 1;
            for (unsigned k = 0; k < users_amount; ++k) {
                Timestamp startTs = generate_random_timestamp(mt, gen);
                Timestamp endTs = generate_random_timestamp(mt, gen);
                if (startTs > endTs) {
                    std::swap(startTs, endTs);
                }
                User *user = new User{startTs, endTs, k, loc_name};
                users.push_back(*user);
                loc_users.push_back(user);
            }
            locations.push_back({loc_name, loc_users});
        }
        std::shuffle(users.begin(), users.end(), mt);
        params.push_back({users, locations});
    }
    return params;
}

constexpr const unsigned ParamsAmount = 20;
INSTANTIATE_TEST_CASE_P(LocationsSplitterTest, LocationsSplitterTest,
                        testing::ValuesIn(generate_params(ParamsAmount)));