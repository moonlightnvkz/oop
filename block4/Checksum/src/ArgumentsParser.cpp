//
// Created by moonlightnvkz on 15.04.17.
//

#include <sstream>
#include "ArgumentsParser.h"

ArgumentsParser::ArgumentsParser(const std::vector<std::string> &keys) {
    for (const auto &k : keys) {
        this->keys.insert(k);
    }
}

std::vector<std::pair<Key, Values>> ArgumentsParser::parse(std::istream &is) {
    std::vector<std::pair<Key, Values>> res;
    std::string value;
    bool key_read = false;
    // skip program name
    while(is >> value) {
        if (keys.find(value) != keys.end()) {
            key_read = true;
            res.push_back({value, {}});
        } else if (key_read){
            res.back().second.push_back(value);
        }
    }
    return res;
}
