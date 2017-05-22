//
// Created by moonlightnvkz on 15.05.17.
//

#include "../include/Tableau.h"

Tableau &Tableau::operator=(const Tableau &that) {
    if (this != &that) {
        this->stacks = that.stacks;
    }
    return *this;
}

Tableau &Tableau::operator=(const Tableau &&that) {
    if (this != &that) {
        this->stacks = std::move(that.stacks);
    }
    return *this;
}
