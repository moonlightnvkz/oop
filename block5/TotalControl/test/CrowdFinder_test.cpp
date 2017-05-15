//
// Created by moonlightnvkz on 01.05.17.
//

#include <gtest/gtest.h>
#include "../src/CrowdFinder.h"
#include "../src/Location.h"
#include "../src/User.h"
#include "../src/Crowd.h"
#include "../src/LocationsSplitter.h"

TEST(CrowdFinderTest, OneLoc_OneCrowd) {
    CrowdFinder finder(4);
    std::string loc_name = "loc";
    std::vector<User*> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{7,7,7,7,7,7};
    users.push_back(new User{startTs, endTs, 0, loc_name});
    users.push_back(new User{startTs, endTs, 1, loc_name});
    users.push_back(new User{startTs, endTs, 2, loc_name});
    users.push_back(new User{startTs, endTs, 3, loc_name});
    users.push_back(new User{Timestamp{3,3,3,3,3,3}, Timestamp{4,4,4,4,4,4}, 4, loc_name});
    users.push_back(new User{Timestamp{8,8,8,8,8,8}, Timestamp{9,9,9,9,9,9}, 5, loc_name});
    Location location(loc_name, users);
    auto crowds = finder.find({location});
    ASSERT_EQ(crowds.size(), 1);
    Crowd &crowd = crowds[0];
    EXPECT_EQ(crowd.startTs(), startTs);
    EXPECT_EQ(crowd.endTs(), endTs);
    EXPECT_EQ(crowd.location(), loc_name);
    EXPECT_EQ(crowd.avg_n(), 4);
    EXPECT_EQ(crowd.max_n(), 4);
    const auto crowd_users = crowd.users();
    ASSERT_EQ(crowd_users.size(), 4);
    for (size_t i = 0; i < 4; ++i) {
        ASSERT_TRUE(crowd_users[i] != nullptr);
        EXPECT_EQ(crowd_users[i], users[i]);
        EXPECT_EQ(*crowd_users[i], *users[i]);
    }
    for (auto u : users) {
        delete u;
    }
}

TEST(CrowdFinderTest, OneLoc_NoCrowds) {
    CrowdFinder finder(4);
    std::string loc_name = "loc";
    std::vector<User*> users;
    Timestamp startTs{0,0,0,0,0,10};
    Timestamp endTs{1,1,1,1,1,1};
    users.push_back(new User{Timestamp{2,2,2,2,2,2}, Timestamp{3,3,3,3,3,3}, 0, loc_name});
    users.push_back(new User{Timestamp{1,1,1,1,1,2}, Timestamp{2,2,2,2,2,2}, 1, loc_name});
    users.push_back(new User{Timestamp{0,0,0,0,0,0}, Timestamp{0,0,0,0,0,9}, 2, loc_name});
    users.push_back(new User{startTs, endTs, 3, loc_name});
    users.push_back(new User{Timestamp{3,3,3,3,3,3}, Timestamp{4,4,4,4,4,4}, 4, loc_name});
    users.push_back(new User{Timestamp{8,8,8,8,8,8}, Timestamp{9,9,9,9,9,9}, 5, loc_name});
    Location location(loc_name, users);
    auto crowds = finder.find({location});
    EXPECT_EQ(crowds.size(), 0);
    for (auto u : users) {
        delete u;
    }
}

TEST(CrowdFinderTest, OneLoc_NotEnoughPeople) {
    CrowdFinder finder(4);
    std::string loc_name = "loc";
    std::vector<User*> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{7,7,7,7,7,7};
    users.push_back(new User{startTs, endTs, 0, loc_name});
    users.push_back(new User{startTs, endTs, 1, loc_name});
    users.push_back(new User{startTs, endTs, 2, loc_name});
    users.push_back(new User{Timestamp{8,8,8,8,8,8}, Timestamp{9,9,9,9,9,9}, 3, loc_name});
    Location location(loc_name, users);
    auto crowds = finder.find({location});
    EXPECT_EQ(crowds.size(), 0);
    for (auto u : users) {
        delete u;
    }
}

TEST(CrowdFinderTest, OneLoc_TwoCrowd) {
    CrowdFinder finder(3);
    std::string loc_name = "loc";
    std::vector<User*> users;
    Timestamp start1Ts{5,5,5,5,5,5};
    Timestamp end1Ts{6,6,6,6,6,6};
    Timestamp start2Ts{7,7,7,7,7,7};
    Timestamp end2Ts{8,8,8,8,8,8};
    users.push_back(new User{start1Ts, end1Ts, 0, loc_name});
    users.push_back(new User{start1Ts, end1Ts, 1, loc_name});
    users.push_back(new User{start1Ts, end1Ts, 2, loc_name});
    users.push_back(new User{start1Ts, end1Ts, 3, loc_name});

    users.push_back(new User{start2Ts, end2Ts, 4, loc_name});
    users.push_back(new User{start2Ts, end2Ts, 5, loc_name});
    users.push_back(new User{start2Ts, end2Ts, 6, loc_name});
    users.push_back(new User{start2Ts, end2Ts, 7, loc_name});
    Location location(loc_name, users);
    auto crowds = finder.find({location});
    ASSERT_EQ(crowds.size(), 2);
    std::vector<std::pair<Timestamp *, Timestamp *>> times{{&start1Ts, &end1Ts},
                                                           {&start2Ts, &end2Ts}};
    size_t size = crowds.size();
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(crowds[i].startTs(), *times[i].first);
        EXPECT_EQ(crowds[i].endTs(), *times[i].second);
        EXPECT_EQ(crowds[i].location(), loc_name);
        EXPECT_EQ(crowds[i].avg_n(), 4);
        EXPECT_EQ(crowds[i].max_n(), 4);
        const auto crowd_users = crowds[i].users();
        ASSERT_EQ(crowd_users.size(), 4);
        for (size_t j = 0; j < 4; ++j) {
            ASSERT_TRUE(crowd_users[j] != nullptr);
            EXPECT_EQ(*crowd_users[j], *users[j + i*4]);
        }
    }
    for (auto u : users) {
        delete u;
    }
}

TEST(CrowdFinderTest, TwoLocs_TwoCrowd) {
    CrowdFinder finder(3);
    std::string loc1_name = "loc1";
    std::string loc2_name = "loc2";
    std::vector<User> users;
    Timestamp start1Ts{5,5,5,5,5,5};
    Timestamp end1Ts{7,7,7,7,7,7};
    Timestamp start2Ts{5,5,5,5,5,5};
    Timestamp end2Ts{7,7,7,7,7,7};
    users.push_back(User{start1Ts, end1Ts, 0, loc1_name});
    users.push_back(User{start1Ts, end1Ts, 1, loc1_name});
    users.push_back(User{start1Ts, end1Ts, 2, loc1_name});
    users.push_back(User{start1Ts, end1Ts, 3, loc1_name});

    users.push_back(User{start2Ts, end2Ts, 4, loc2_name});
    users.push_back(User{start2Ts, end2Ts, 5, loc2_name});
    users.push_back(User{start2Ts, end2Ts, 6, loc2_name});
    users.push_back(User{start2Ts, end2Ts, 7, loc2_name});
    std::vector<Location> locations = LocationsSplitter::split(users);
    auto crowds = finder.find(locations);
    ASSERT_EQ(crowds.size(), 2);
    std::vector<std::pair<Timestamp *, Timestamp *>> times{{&start1Ts, &end1Ts},
                                                           {&start2Ts, &end2Ts}};
    std::vector<std::string *> names{&loc1_name, &loc2_name};
    size_t size = crowds.size();
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(crowds[i].startTs(), *times[i].first);
        EXPECT_EQ(crowds[i].endTs(), *times[i].second);
        EXPECT_EQ(crowds[i].location(), *names[i]);
        EXPECT_EQ(crowds[i].avg_n(), 4);
        EXPECT_EQ(crowds[i].max_n(), 4);
        const auto crowd_users = crowds[i].users();
        ASSERT_EQ(crowd_users.size(), 4);
        for (size_t j = 0; j < 4; ++j) {
            ASSERT_TRUE(crowd_users[j] != nullptr);
            EXPECT_EQ(*crowd_users[j], users[j + i*4]);
        }
    }
}

TEST(CrowdFinderTest, TwoLocs_ThreeCrowd) {
    CrowdFinder finder(2);
    std::string loc1_name = "loc1";
    std::string loc2_name = "loc2";
    std::vector<User> users;
    Timestamp start1Ts{1,1,1,1,1,1};
    Timestamp end1Ts{2,2,2,2,2,2};
    Timestamp start2Ts{3,3,3,3,3,3};
    Timestamp end2Ts{4,4,4,4,4,4};
    Timestamp start3Ts{4,4,4,4,4,4};
    Timestamp end3Ts{5,5,5,5,5,5};
    users.push_back(User{start1Ts, end1Ts, 0, loc1_name});
    users.push_back(User{start1Ts, end1Ts, 1, loc1_name});
    users.push_back(User{start2Ts, end2Ts, 2, loc1_name});
    users.push_back(User{start2Ts, end2Ts, 3, loc1_name});
    users.push_back(User{start3Ts, end3Ts, 4, loc2_name});
    users.push_back(User{start3Ts, end3Ts, 5, loc2_name});

    std::vector<Location> locations = LocationsSplitter::split(users);
    auto crowds = finder.find(locations);
    ASSERT_EQ(crowds.size(), 3);
    std::vector<std::pair<Timestamp *, Timestamp *>> times{{&start1Ts, &end1Ts},
                                                           {&start2Ts, &end2Ts},
                                                           {&start3Ts, &end3Ts}};
    std::vector<std::string *> names{&loc1_name, &loc1_name, &loc2_name};
    size_t size = crowds.size();
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(crowds[i].startTs(), *times[i].first);
        EXPECT_EQ(crowds[i].endTs(), *times[i].second);
        EXPECT_EQ(crowds[i].location(), *names[i]);
        EXPECT_EQ(crowds[i].avg_n(), 2);
        EXPECT_EQ(crowds[i].max_n(), 2);
        const auto crowd_users = crowds[i].users();
        ASSERT_EQ(crowd_users.size(), 2);
        for (size_t j = 0; j < 2; ++j) {
            ASSERT_TRUE(crowd_users[j] != nullptr);
            EXPECT_EQ(*crowd_users[j], users[j + i*2]);
        }
    }
}