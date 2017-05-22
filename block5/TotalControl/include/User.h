//
// Created by moonlightnvkz on 24.04.17.
//

#pragma once

#include <string>
#include "Timestamp.h"

class User {
public:
    User(const Timestamp &startTs, const Timestamp &endTs, const unsigned id) :
            startTs_(startTs), endTs_(endTs), id_(id) { };

    virtual ~User() {
    };
    // Getters/Setters

    const Timestamp &startTs() const { return startTs_; }

    void startTs(const Timestamp &startTs) { startTs_ = startTs; }

    const Timestamp &endTs() const { return endTs_; }

    void endTs(const Timestamp &endTs) { endTs_ = endTs; }

    unsigned int id() const { return id_; }

    void id(unsigned int id) { id_ = id; }

    // End Getters/Setters
private:
    Timestamp startTs_;

    Timestamp endTs_;

    unsigned id_;

    friend bool operator==(const User &a, const User &b);

    friend std::ostream &operator<<(std::ostream &os, const User &user);
};

bool operator==(const User &a, const User &b);

std::ostream &operator<<(std::ostream &os, const User &user);