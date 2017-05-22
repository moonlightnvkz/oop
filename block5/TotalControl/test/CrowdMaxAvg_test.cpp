//
// Created by moonlightnvkz on 30.04.17.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../include/Crowd.h"
#include "../include/User.h"

TEST(CrowdMaxAvgTest, TEST1) {
    std::vector<std::shared_ptr<User>> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{10,10,10,10,10,10};
    unsigned id = 0;
    std::string location{"1"};
    users.push_back(std::make_shared<User>(Timestamp{1,1,1,1,1,1}, Timestamp{5,5,5,5,5,5}, id++));
    users.push_back(std::make_shared<User>(Timestamp{1,1,1,1,1,1}, Timestamp{6,6,6,6,6,6}, id++));
    users.push_back(std::make_shared<User>(Timestamp{5,5,5,5,5,5}, Timestamp{5,5,5,5,5,5}, id++));
    users.push_back(std::make_shared<User>(Timestamp{5,5,5,5,5,5}, Timestamp{10,10,10,10,10,10}, id++));
    users.push_back(std::make_shared<User>(Timestamp{10,10,10,10,10,10}, Timestamp{11,11,11,11,11,11}, id++));
    users.push_back(std::make_shared<User>(Timestamp{9,9,9,9,9,9}, Timestamp{11,11,11,11,11,11}, id++));
    users.push_back(std::make_shared<User>(Timestamp{7,7,7,7,7,7}, Timestamp{9,9,9,9,9,9}, id));

    Crowd crowd{location, startTs, endTs, users};

    EXPECT_EQ(crowd.max_n(), 4);
    EXPECT_EQ(crowd.avg_n(), 1);
}

TEST(CrowdMaxAvgTest, TEST2) {
    std::vector<std::shared_ptr<User>> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{10,10,10,10,10,10};
    unsigned id = 0;
    std::string location{"1"};
    users.push_back(std::make_shared<User>(Timestamp{1,1,1,1,1,1}, Timestamp{5,5,5,5,5,5}, id++));
    users.push_back(std::make_shared<User>(Timestamp{10,10,10,10,10,10}, Timestamp{11,11,11,11,11,11}, id));

    Crowd crowd{location, startTs, endTs, users};

    EXPECT_EQ(crowd.max_n(), 1);
    EXPECT_EQ(crowd.avg_n(), 0);
}

TEST(CrowdMaxAvgTest, TEST3) {
    std::vector<std::shared_ptr<User>> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{10,10,10,10,10,10};
    unsigned id = 0;
    std::string location{"1"};
    users.push_back(std::make_shared<User>(Timestamp{5,5,5,5,5,5}, Timestamp{10,10,10,10,10,10}, id++));

    Crowd crowd{location, startTs, endTs, users};

    EXPECT_EQ(crowd.max_n(), 1);
    EXPECT_EQ(crowd.avg_n(), 1);
}