//
// Created by moonlightnvkz on 24.04.17.
//

#pragma once

#include <vector>
#include <string>
#include "Timestamp.h"

class User;

class Crowd {
public:
    Crowd(const std::string &location, const Timestamp &startTs, const Timestamp &endTs,
          const std::vector<User *> &users);

    Crowd(const std::string &location, const Timestamp &startTs, const Timestamp &endTs,
          std::vector<User *> &&users);

    void add_user(User * user);

    friend std::ostream &operator<<(std::ostream &os, Crowd &crowd);

    // Getters/Setters

    const Timestamp &startTs() const { return _startTs; }

    const Timestamp &endTs() const { return _endTs; }

    unsigned int max_n();

    unsigned int avg_n();

    const std::string &location() const { return _location; }

    void location(const std::string &location) { Crowd::_location = location; }

    const std::vector<User*> &users() const { return _users; }

    // End Getters/Setters
private:
    void calc_max();

    void calc_avg();

    Timestamp _startTs;

    Timestamp _endTs;

    std::string _location;

    bool _max_calculated;

    bool _avg_calculated;

    unsigned _max_n;

    unsigned _avg_n;

    std::vector<User*> _users;
};

std::ostream &operator<<(std::ostream &os, const Crowd &crowd);