//
// Created by moonlightnvkz on 24.04.17.
//

#include <tuple>
#include "VisitsListReader.h"

bool VisitsListReader::read(std::istream &is, std::vector<User> &list) {
    Timestamp startTs;
    Timestamp endTs;
    unsigned user_id;
    std::string location;

    while (is >> startTs && is.ignore(3) >> endTs >> user_id && std::getline(is.ignore(1), location)) {
        list.push_back(User(startTs, endTs, user_id, location));
    }
    return is.eof();
}
