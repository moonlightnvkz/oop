//
// Created by moonlightnvkz on 23.02.17.
//

#include "DSU.h"

using namespace std;

void DSU::add_set(unsigned s) {
    if (s >= parents.size()) {
        parents.resize(s + 1);
        ranks.resize(s + 1);
    }
    parents.at(s) = s;
    ranks.at(s) = 0;
}

unsigned DSU::find_set(unsigned s) {
    if (s == parents.at(s)) {
        return s;
    }
    return parents.at(s) = find_set(parents.at(s));
}

void DSU::unite_sets(unsigned s1, unsigned s2) {
    s1 = find_set(s1);
    s2 = find_set(s2);
    if (s1 != s2) {
        if (ranks.at(s1) < ranks.at(s2)) {
            swap(s1, s2);
        }
        parents.at(s2) = s1;
        if (ranks.at(s1) == ranks.at(s2)) {
            ++ranks.at(s1);
        }
    }
}
