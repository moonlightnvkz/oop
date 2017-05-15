//
// Created by moonlightnvkz on 29.04.17.
//

#pragma once

#include <vector>
#include <string>

class User;

class Location {
public:
    Location(std::string name, const std::vector<User*> &users)
            : _name(name), _users(users) { }

    Location(std::string name, std::vector<User*> &&users)
            : _name(name), _users(std::move(users)) {}


    std::string name() const { return _name; }

    void name(std::string name) { _name = name; }

    const std::vector<User*> &users() const { return _users; }

    void users(const std::vector<User*> &users) { _users = users; }

    void users(std::vector<User*> &&users) { _users = std::move(users); }

    void add_user(User *user) { _users.push_back(user); }

private:
    std::string _name;
    std::vector<User*> _users;
};


