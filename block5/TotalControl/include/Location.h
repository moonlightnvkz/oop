//
// Created by moonlightnvkz on 29.04.17.
//

#pragma once

#include <vector>
#include <string>
#include <memory>

class User;

class Location {
public:
    Location(const std::string &name, const std::vector<std::shared_ptr<User>> &users)
            : name_(name), users_(users) { }

    Location(const std::string &name, std::vector<std::shared_ptr<User>> &&users)
            : name_(name), users_(std::move(users)) {}

    virtual ~Location() { }

    const std::string &name() const { return name_; }

    void name(const std::string &name) { name_ = name; }

    const std::vector<std::shared_ptr<User>> &users() const { return users_; }

    void users(const std::vector<std::shared_ptr<User>> &users) { users_ = users; }

    void users(std::vector<std::shared_ptr<User>> &&users) { users_ = users; }

    void add_user(std::shared_ptr<User> user) { users_.push_back(user); }

private:
    std::string name_;
    std::vector<std::shared_ptr<User>> users_;
};


