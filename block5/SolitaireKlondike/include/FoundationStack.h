//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once

#include <vector>
#include "CardContainer.h"

class FoundationStack : public CardContainer{
public:
    FoundationStack () { };

    ~FoundationStack() { };

    FoundationStack (FoundationStack  &&stack) : CardContainer(std::move(stack.cards)) { }

    FoundationStack &operator=(FoundationStack &&that);

    virtual bool is_suitable(const Card *card) const override;
};


