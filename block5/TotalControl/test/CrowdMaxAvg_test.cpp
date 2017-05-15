//
// Created by moonlightnvkz on 30.04.17.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../src/Crowd.h"
#include "../src/User.h"

TEST(CrowdMaxAvgTest, TEST1) {
    std::vector<User*> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{10,10,10,10,10,10};
    unsigned id = 0;
    std::string location{"1"};
    users.push_back(new User({1,1,1,1,1,1}, {5,5,5,5,5,5}, id++, location));
    users.push_back(new User({1,1,1,1,1,1}, {6,6,6,6,6,6}, id++, location));
    users.push_back(new User({5,5,5,5,5,5}, {5,5,5,5,5,5}, id++, location));
    users.push_back(new User({5,5,5,5,5,5}, {10,10,10,10,10,10}, id++, location));
    users.push_back(new User({10,10,10,10,10,10}, {11,11,11,11,11,11}, id++, location));
    users.push_back(new User({9,9,9,9,9,9}, {11,11,11,11,11,11}, id++, location));
    users.push_back(new User({7,7,7,7,7,7}, {9,9,9,9,9,9}, id, location));

    Crowd crowd{location, startTs, endTs, users};

    EXPECT_EQ(crowd.max_n(), 4);
    EXPECT_EQ(crowd.avg_n(), 1);

    size_t size = users.size();
    for (size_t i = 0; i < size; ++i) {
        delete users[i];
    }
}

TEST(CrowdMaxAvgTest, TEST2) {
    std::vector<User*> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{10,10,10,10,10,10};
    unsigned id = 0;
    std::string location{"1"};
    users.push_back(new User({1,1,1,1,1,1}, {5,5,5,5,5,5}, id++, location));
    users.push_back(new User({10,10,10,10,10,10}, {11,11,11,11,11,11}, id++, location));

    Crowd crowd{location, startTs, endTs, users};

    EXPECT_EQ(crowd.max_n(), 1);
    EXPECT_EQ(crowd.avg_n(), 0);

    size_t size = users.size();
    for (size_t i = 0; i < size; ++i) {
        delete users[i];
    }
}

TEST(CrowdMaxAvgTest, TEST3) {
    std::vector<User*> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{10,10,10,10,10,10};
    unsigned id = 0;
    std::string location{"1"};
    users.push_back(new User({5,5,5,5,5,5}, {10,10,10,10,10,10}, id++, location));

    Crowd crowd{location, startTs, endTs, users};

    EXPECT_EQ(crowd.max_n(), 1);
    EXPECT_EQ(crowd.avg_n(), 1);

    size_t size = users.size();
    for (size_t i = 0; i < size; ++i) {
        delete users[i];
    }
}