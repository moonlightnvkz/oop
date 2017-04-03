//
// Created by moonlightnvkz on 03.04.17.
//

#include <istream>
#include "TopoSorterParser.h"

std::vector<TopoSorter::Node> TopoSorterParser::parse(std::istream &is) {
    if (!is) {
        throw std::invalid_argument("Bad istream");
    }
    std::vector<TopoSorter::Node> nodes;

    while (is) {
        std::string in;
        std::getline(is, in, '\n');
        if (!is) {
            break;
        }
        std::vector<std::string> result{
                tokenize(in, "=,", true)
        };

        auto it = result.begin();
        TopoSorter::Name name{*it++};
        TopoSorter::Dependencies dependencies{it, result.end()};
        nodes.push_back(std::make_pair(name, dependencies));
    }
    return nodes;
}

std::vector<std::string> TopoSorterParser::tokenize(const std::string &str,
                                                    const std::string &delimeter,
                                                    bool remove_surrounding_spaces) {
    std::string::size_type last_pos = 0;
    std::string::size_type pos = 0;

    last_pos = str.find_first_not_of(delimeter);
    pos = str.find_first_of(delimeter, last_pos);

    std::vector<std::string> tokens;
    while (pos != str.npos || last_pos != str.npos) {
        std::string token = str.substr(last_pos, pos - last_pos);
        auto it_f = token.begin();
        auto it_l = token.end();
        if (remove_surrounding_spaces) {

            if (*it_f == ' ') {
                it_f++;
            }
            if (*(it_l - 1) == ' ') {
                it_l--;
            }
        }
        if (it_f < it_l) {
            tokens.push_back({it_f, it_l});
        }
        last_pos = str.find_first_not_of(delimeter, pos);
        pos = str.find_first_of(delimeter, last_pos);
    }
    return tokens;
}
