//
// Created by moonlightnvkz on 08.05.17.
//

#pragma once


#include "CardContainer.h"

class TableauStack : public CardContainer{
public:
    TableauStack() {};

    ~TableauStack() { };

    TableauStack(TableauStack &&stack) : CardContainer(std::move(stack.cards)) { }

    TableauStack(std::vector<std::unique_ptr<Card>> &&cards) : CardContainer(std::move(cards)) {}

    using CardContainer::push_back;

    bool push_back(TableauStack &&stack);

    virtual void pop_back() override;

    void pop_tale(size_t amount);

    TableauStack tale(size_t amount);

    virtual bool is_suitable(const Card *card) const override;

    TableauStack &operator=(TableauStack &&that);
};