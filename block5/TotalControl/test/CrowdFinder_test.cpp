//
// Created by moonlightnvkz on 01.05.17.
//

#include <gtest/gtest.h>
#include "../include/CrowdFinder.h"
#include "../include/Location.h"
#include "../include/User.h"
#include "../include/Crowd.h"

TEST(CrowdFinderTest, OneLoc_OneCrowd) {
    CrowdFinder finder(4);
    std::string loc_name = "loc";
    std::vector<std::shared_ptr<User>> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{7,7,7,7,7,7};
    users.push_back(std::make_shared<User>(startTs, endTs, 0));
    users.push_back(std::make_shared<User>(startTs, endTs, 1));
    users.push_back(std::make_shared<User>(startTs, endTs, 2));
    users.push_back(std::make_shared<User>(startTs, endTs, 3));
    users.push_back(std::make_shared<User>(Timestamp{3,3,3,3,3,3}, Timestamp{4,4,4,4,4,4}, 4));
    users.push_back(std::make_shared<User>(Timestamp{8,8,8,8,8,8}, Timestamp{9,9,9,9,9,9}, 5));
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
        EXPECT_EQ(*crowd_users[i].get(), *users[i]);
    }
}

TEST(CrowdFinderTest, OneLoc_NoCrowds) {
    CrowdFinder finder(4);
    std::string loc_name = "loc";
    std::vector<std::shared_ptr<User>> users;
    Timestamp startTs{0,0,0,0,0,10};
    Timestamp endTs{1,1,1,1,1,1};
    users.push_back(std::make_shared<User>(Timestamp{2,2,2,2,2,2}, Timestamp{3,3,3,3,3,3}, 0));
    users.push_back(std::make_shared<User>(Timestamp{1,1,1,1,1,2}, Timestamp{2,2,2,2,2,2}, 1));
    users.push_back(std::make_shared<User>(Timestamp{0,0,0,0,0,0}, Timestamp{0,0,0,0,0,9}, 2));
    users.push_back(std::make_shared<User>(startTs, endTs, 3));
    users.push_back(std::make_shared<User>(Timestamp{3,3,3,3,3,3}, Timestamp{4,4,4,4,4,4}, 4));
    users.push_back(std::make_shared<User>(Timestamp{8,8,8,8,8,8}, Timestamp{9,9,9,9,9,9}, 5));
    Location location(loc_name, users);
    auto crowds = finder.find({location});
    EXPECT_EQ(crowds.size(), 0);
}

TEST(CrowdFinderTest, OneLoc_OneUser) {
    CrowdFinder finder(0);
    std::string loc_name = "loc";
    std::vector<std::shared_ptr<User>> users;
    Timestamp startTs{0,0,0,0,0,10};
    Timestamp endTs{1,1,1,1,1,1};
    users.push_back(std::make_shared<User>(startTs, endTs, 0));
    Location location(loc_name, users);
    auto crowds = finder.find({location});
    EXPECT_EQ(crowds.size(), 1);
}

TEST(CrowdFinderTest, TwoLoc_OneUser_CritZero) {
    CrowdFinder finder(0);
    std::string loc1_name = "loc1";
    std::string loc2_name = "loc2";
    std::vector<std::shared_ptr<User>> users;
    Timestamp startTs{0, 0, 0, 0, 0, 10};
    Timestamp endTs{1, 1, 1, 1, 1, 1};
    users.push_back(std::make_shared<User>(startTs, endTs, 0));
    Location location1(loc1_name, users);
    Location location2(loc2_name, {});
    auto crowds = finder.find({location1, location2});
    EXPECT_EQ(crowds.size(), 1);
}

TEST(CrowdFinderTest, TwoLoc_OneUser_CritOne) {
    CrowdFinder finder(1);
    std::string loc1_name = "loc1";
    std::string loc2_name = "loc2";
    std::vector<std::shared_ptr<User>> users;
    Timestamp startTs{0, 0, 0, 0, 0, 10};
    Timestamp endTs{1, 1, 1, 1, 1, 1};
    users.push_back(std::make_shared<User>(startTs, endTs, 0));
    Location location1(loc1_name, users);
    Location location2(loc2_name, {});
    auto crowds = finder.find({location1, location2});
    EXPECT_EQ(crowds.size(), 1);
}

TEST(CrowdFinderTest, TwoLoc_ZeroUsers_CritOne) {
    CrowdFinder finder(1);
    std::string loc1_name = "loc1";
    std::string loc2_name = "loc2";
    Location location1(loc1_name, {});
    Location location2(loc2_name, {});
    auto crowds = finder.find({location1, location2});
    EXPECT_EQ(crowds.size(), 0);
}

TEST(CrowdFinderTest, OneLoc_NotEnoughPeople) {
    CrowdFinder finder(4);
    std::string loc_name = "loc";
    std::vector<std::shared_ptr<User>> users;
    Timestamp startTs{5,5,5,5,5,5};
    Timestamp endTs{7,7,7,7,7,7};
    users.push_back(std::make_shared<User>(startTs, endTs, 0));
    users.push_back(std::make_shared<User>(startTs, endTs, 1));
    users.push_back(std::make_shared<User>(startTs, endTs, 2));
    users.push_back(std::make_shared<User>(Timestamp{8,8,8,8,8,8}, Timestamp{9,9,9,9,9,9}, 3));
    Location location(loc_name, users);
    auto crowds = finder.find({location});
    EXPECT_EQ(crowds.size(), 0);
}

TEST(CrowdFinderTest, OneLoc_TwoCrowd) {
    CrowdFinder finder(3);
    std::string loc_name = "loc";
    std::vector<std::shared_ptr<User>> users;
    Timestamp start1Ts{5,5,5,5,5,5};
    Timestamp end1Ts{6,6,6,6,6,6};
    Timestamp start2Ts{7,7,7,7,7,7};
    Timestamp end2Ts{8,8,8,8,8,8};
    users.push_back(std::make_shared<User>(start1Ts, end1Ts, 0));
    users.push_back(std::make_shared<User>(start1Ts, end1Ts, 1));
    users.push_back(std::make_shared<User>(start1Ts, end1Ts, 2));
    users.push_back(std::make_shared<User>(start1Ts, end1Ts, 3));

    users.push_back(std::make_shared<User>(start2Ts, end2Ts, 4));
    users.push_back(std::make_shared<User>(start2Ts, end2Ts, 5));
    users.push_back(std::make_shared<User>(start2Ts, end2Ts, 6));
    users.push_back(std::make_shared<User>(start2Ts, end2Ts, 7));
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
            EXPECT_EQ(*crowd_users[j].get(), *users[j + i*4]);
        }
    }
}

TEST(CrowdFinderTest, TwoLocs_TwoCrowd) {
    CrowdFinder finder(3);
    std::string loc1_name = "loc1";
    std::string loc2_name = "loc2";
    std::vector<std::shared_ptr<User>> users1;
    std::vector<std::shared_ptr<User>> users2;
    Timestamp start1Ts{5,5,5,5,5,5};
    Timestamp end1Ts{7,7,7,7,7,7};
    Timestamp start2Ts{5,5,5,5,5,5};
    Timestamp end2Ts{7,7,7,7,7,7};
    users1.push_back(std::make_shared<User>(start1Ts, end1Ts, 0));
    users1.push_back(std::make_shared<User>(start1Ts, end1Ts, 1));
    users1.push_back(std::make_shared<User>(start1Ts, end1Ts, 2));
    users1.push_back(std::make_shared<User>(start1Ts, end1Ts, 3));

    users2.push_back(std::make_shared<User>(start2Ts, end2Ts, 4));
    users2.push_back(std::make_shared<User>(start2Ts, end2Ts, 5));
    users2.push_back(std::make_shared<User>(start2Ts, end2Ts, 6));
    users2.push_back(std::make_shared<User>(start2Ts, end2Ts, 7));
    std::vector<Location> locations{Location(loc1_name, users1), Location(loc2_name, users2)};
    auto crowds = finder.find(locations);
    ASSERT_EQ(crowds.size(), 2);
    std::vector<std::pair<Timestamp *, Timestamp *>> times{{&start1Ts, &end1Ts},
                                                           {&start2Ts, &end2Ts}};
    std::vector<std::vector<std::shared_ptr<User>>*> users{&users1, &users2};
    size_t size = crowds.size();
    for (size_t i = 0; i < size; ++i) {
        EXPECT_EQ(crowds[i].startTs(), *times[i].first);
        EXPECT_EQ(crowds[i].endTs(), *times[i].second);
        EXPECT_EQ(crowds[i].avg_n(), 4);
        EXPECT_EQ(crowds[i].max_n(), 4);
        const auto crowd_users = crowds[i].users();
        ASSERT_EQ(crowd_users.size(), 4);
    }
}

TEST(CrowdFinderTest, TwoLocs_ThreeCrowd) {
    CrowdFinder finder(2);
    std::string loc1_name = "loc1";
    std::string loc2_name = "loc2";
    std::vector<std::shared_ptr<User>> users1;
    std::vector<std::shared_ptr<User>> users2;
    Timestamp start1Ts{1,1,1,1,1,1};
    Timestamp end1Ts{2,2,2,2,2,2};
    Timestamp start2Ts{3,3,3,3,3,3};
    Timestamp end2Ts{4,4,4,4,4,4};
    Timestamp start3Ts{4,4,4,4,4,4};
    Timestamp end3Ts{5,5,5,5,5,5};
    users1.push_back(std::make_shared<User>(start1Ts, end1Ts, 0));
    users1.push_back(std::make_shared<User>(start1Ts, end1Ts, 1));
    users1.push_back(std::make_shared<User>(start2Ts, end2Ts, 2));
    users1.push_back(std::make_shared<User>(start2Ts, end2Ts, 3));
    users2.push_back(std::make_shared<User>(start3Ts, end3Ts, 4));
    users2.push_back(std::make_shared<User>(start3Ts, end3Ts, 5));

    std::vector<Location> locations{Location(loc1_name, users1), Location(loc2_name, users2)};
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
        EXPECT_EQ(crowds[i].avg_n(), 2);
        EXPECT_EQ(crowds[i].max_n(), 2);
        const auto crowd_users = crowds[i].users();
        ASSERT_EQ(crowd_users.size(), 2);
    }
}