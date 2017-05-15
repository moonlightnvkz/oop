//
// Created by moonlightnvkz on 29.04.17.
//

#pragma once

#include <vector>

class Location;
class User;

class LocationsSplitter {
public:
    LocationsSplitter() = delete;

    static std::vector<Location> split(const std::vector<User> &list);
};


