//
// Created by moonlightnvkz on 17.04.17.
//

#pragma once


#include <istream>

using Manifest = std::vector<std::pair<std::string, uint16_t>>;

class ManifestReader {
public:
    ManifestReader() = delete;

    static bool read(std::istream &is, Manifest &manifest);
};


