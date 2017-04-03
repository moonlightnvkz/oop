//
// Created by moonlightnvkz on 03.04.17.
//

#pragma once
#include <vector>
#include <string>

class Tokenizer {
public:
    Tokenizer() = delete;

    std::vector<std::string> tokenize(const std::string &str,
                                      const std::string &delimeter,
                                      bool remove_surrounding_spaces);
};