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

std::vector<std::pair<Key, Values>> ArgumentsParser::parse(const int argc, char *argv[]) {
    std::vector<std::pair<Key, Values>> res;
    // skip program name
    std::string value;
    bool key_read = false;
    for (int i = 1; i < argc; ++i) {
        std::stringstream ss(argv[i]);
        ss >> value;
        if (keys.find(value) != keys.end()) {
            key_read = true;
            res.push_back({value, {}});
        } else {
            if (!key_read) {
                return {};
            }
            res.back().second.push_back(value);
        }
    }
    return res;
}
