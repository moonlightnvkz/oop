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
            : critical_amount_(critical_amount) {
    }

    virtual ~CrowdFinder() {};

    std::vector<Crowd> find(const std::vector<Location> &list);

private:
    unsigned critical_amount_;
};


