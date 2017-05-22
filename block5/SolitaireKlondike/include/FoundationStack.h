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
    FoundationStack (const FoundationStack &stack) : CardContainer(stack.cards) { }

    FoundationStack (FoundationStack  &&stack) : CardContainer(std::move(stack.cards)) { }

    FoundationStack &operator=(const FoundationStack &that);

    FoundationStack &operator=(FoundationStack &&that);

    virtual bool is_suitable(const std::shared_ptr<Card> &card) const override;
};


