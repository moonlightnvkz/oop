//
// Created by moonlightnvkz on 24.04.17.
//

#include <tuple>
#include <map>
#include "../include/VisitsListReader.h"

bool VisitsListReader::read(std::istream &is, std::vector<Location> &list) {
    Timestamp startTs;
    Timestamp endTs;
    unsigned user_id;
    std::string location;
    std::map<std::string, Location> map;
    while (is >> startTs && is.ignore(3) >> endTs >> user_id && std::getline(is.ignore(1), location)) {
        if (map.find(location) == map.end()) {
            map.emplace(location, Location(location, {std::make_shared<User>(startTs, endTs, user_id)}));
        } else {
            map.at(location).add_user(std::make_shared<User>(startTs, endTs, user_id));
        }
    }
    return is.eof();
}
