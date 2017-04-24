//
// Created by moonlightnvkz on 22.04.17.
//

#include "ManifestWriter.h"

bool ManifestWriter::write(std::ostream &os, const Manifest &manifest) {
    for (const auto &entry : manifest) {
        if (!(os << entry.first << ":" << entry.second << std::endl)) {
            return false;
        }
    }
    return true;
}
