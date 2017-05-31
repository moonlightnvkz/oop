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

    Tableau(Tableau &&tableau) : stacks(std::move(tableau.stacks)) { }

    Tableau(std::array<TableauStack, 7> &&stacks) : stacks(std::move(stacks)){ }

    TableauStack &stack(size_t i) { return stacks.at(i); }

    Tableau &operator=(Tableau &&that);

private:
    std::array<TableauStack, 7> stacks;
};
