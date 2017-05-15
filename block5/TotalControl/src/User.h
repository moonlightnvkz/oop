//
// Created by moonlightnvkz on 24.04.17.
//

#pragma once

#include <string>
#include "Timestamp.h"

class User {
public:
    User(const Timestamp &startTs, const Timestamp &endTs, const unsigned id, const std::string &location) :
            _startTs(startTs), _endTs(endTs), _id(id), _location(location) { };

    // Getters/Setters

    const Timestamp &startTs() const { return _startTs; }

    void startTs(const Timestamp &startTs) { User::_startTs = startTs; }

    const Timestamp &endTs() const { return _endTs; }

    void endTs(const Timestamp &endTs) { User::_endTs = endTs; }

    unsigned int id() const { return _id; }

    void id(unsigned int id) { User::_id = id; }

    const std::string &location() const { return _location; }

    void location(const std::string &location) { User::_location = location; }

    // End Getters/Setters
private:
    Timestamp _startTs;

    Timestamp _endTs;

    unsigned _id;

    std::string _location;

    friend bool operator==(const User &a, const User &b);

    friend std::ostream &operator<<(std::ostream &os, const User &user);
};

bool operator==(const User &a, const User &b);

std::ostream &operator<<(std::ostream &os, const User &user);