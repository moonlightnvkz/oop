//
// Created by moonlightnvkz on 17.04.17.
//

#include <vector>
#include "ManifestReader.h"

bool ManifestReader::read(std::istream &is, Manifest &manifest) {
    std::string f;
    int checksum;
    while (std::getline(is, f, ':') && (is >> checksum)) {
        manifest.push_back({f, checksum});
        // ignore the rest of the line (mainly for ignoring \n)
        std::getline(is, f, '\n');
    }
    if (!is.eof()) {
        return false;
    }
    return true;
}
