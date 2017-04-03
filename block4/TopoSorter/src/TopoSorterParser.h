//
// Created by moonlightnvkz on 03.04.17.
//

#pragma once
#include <vector>
#include <string>
#include "TopoSorter.h"

class TopoSorterParser {
public:
    TopoSorterParser() = delete;

    static std::vector<TopoSorter::Node> parse(std::istream &is);

private:
    static std::vector<std::string> tokenize(const std::string &str,
                                             const std::string &delimeter,
                                             bool remove_surrounding_spaces);
};


