//
// Created by moonlightnvkz on 22.04.17.
//

#pragma once


#include <ostream>
#include <vector>

using Manifest = std::vector<std::pair<std::string, uint16_t>>;

class ManifestWriter {
public:
    ManifestWriter() = delete;

    static bool write(std::ostream &os, const Manifest &manifest);
};


