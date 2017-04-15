//
// Created by moonlightnvkz on 15.04.17.
//

#pragma once

#include <vector>
#include <string>
#include <unordered_set>

using Key = std::string;
using Values = std::vector<std::string>;

class ArgumentsParser {
public:
    ArgumentsParser(const std::vector<std::string> &keys);

    ArgumentsParser(std::initializer_list<std::string> keys) : keys(keys) { };

    ArgumentsParser(const std::unordered_set<std::string> &keys) : keys(keys) { };

    ArgumentsParser(std::unordered_set<std::string> &&keys) : keys(std::move(keys)) { };


    std::vector<std::pair<Key, Values>> parse(const int argc, char *argv[]);

private:
    std::unordered_set<std::string> keys;
};


