//
// Created by moonlightnvkz on 24.04.17.
//

#pragma once
#include <istream>
#include <vector>
#include "Timestamp.h"
#include "User.h"
#include "Location.h"

class VisitsListReader {
public:
    VisitsListReader() = delete;

    static bool read(std::istream &is, std::vector<Location> &list);
};


