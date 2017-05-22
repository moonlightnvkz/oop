//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once


#include <array>
#include "TableauStack.h"

class Tableau {
public:
    Tableau() { }

    virtual ~Tableau() { }

    Tableau(const Tableau &tableau) : stacks(tableau.stacks) { }

    Tableau(Tableau &&tableau) : stacks(std::move(tableau.stacks)) { }

    Tableau(const std::array<TableauStack, 7> &stacks) : stacks(stacks){ }

    Tableau(std::array<TableauStack, 7> &&stacks) : stacks(std::move(stacks)){ }

    TableauStack &stack(size_t i) { return stacks.at(i); }

    Tableau &operator=(const Tableau &that);

    Tableau &operator=(const Tableau &&that);

private:
    std::array<TableauStack, 7> stacks;
};
