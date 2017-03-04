//
// Created by moonlightnvkz on 23.02.17.
//

#pragma once

#include <vector>
#include <unordered_map>

class DSU {
public:
    void add_set(unsigned s);

    unsigned find_set(unsigned s);

    void unite_sets(unsigned s1, unsigned s2);

private:
    std::vector<unsigned> parents;
    std::vector<unsigned> ranks;
};


