//
// Created by moonlightnvkz on 24.04.17.
//

#pragma once

#include <vector>
#include <string>
#include <memory>
#include "Timestamp.h"

class User;

class Crowd {
public:
    Crowd(const std::string &location, const Timestamp &startTs, const Timestamp &endTs,
          const std::vector<std::shared_ptr<User>> &users);

    Crowd(const std::string &location, const Timestamp &startTs, const Timestamp &endTs,
          std::vector<std::shared_ptr<User>> &&users);

    virtual ~Crowd() {};

    void add_user(std::shared_ptr<User> user);

    friend std::ostream &operator<<(std::ostream &os, Crowd &crowd);

    // Getters/Setters

    const Timestamp &startTs() const { return startTs_; }

    const Timestamp &endTs() const { return endTs_; }

    unsigned int max_n();

    unsigned int avg_n();

    const std::string &location() const { return location_; }

    void location(const std::string &location) { Crowd::location_ = location; }

    const std::vector<std::shared_ptr<User>> &users() const { return users_; }

    // End Getters/Setters
private:
    void calc_max();

    void calc_avg();

    Timestamp startTs_;

    Timestamp endTs_;

    std::string location_;

    bool max_calculated_;

    bool avg_calculated_;

    unsigned max_n_;

    unsigned avg_n_;

    std::vector<std::shared_ptr<User>> users_;
};

std::ostream &operator<<(std::ostream &os, const Crowd &crowd);