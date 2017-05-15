//
// Created by moonlightnvkz on 29.04.17.
//

#include <map>
#include "LocationsSplitter.h"
#include "Location.h"
#include "User.h"

std::vector<Location> LocationsSplitter::split(const std::vector<User> &list) {
    std::map<std::string, Location> map;
    for (const auto &user : list) {
        std::string loc = user.location();
        if (map.find(loc) == map.end()) {
            map.emplace(loc, Location(loc, {const_cast<User*>(&user)}));
        } else {
            map.at(loc).add_user(const_cast<User *>(&user));
        }
    }

    std::vector<Location> locations;
    for (const auto loc : map) {
        locations.push_back(loc.second);
    }
    return locations;
}
