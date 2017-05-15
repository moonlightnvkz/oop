//
// Created by moonlightnvkz on 29.04.17.
//

#pragma once


#include <vector>

class Crowd;
class Location;

class CrowdFinder {
public:
    CrowdFinder(const unsigned critical_amount)
            : _critical_amount(critical_amount) {
    }

    std::vector<Crowd> find(const std::vector<Location> &list);

private:
    unsigned _critical_amount;
};


