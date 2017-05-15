//
// Created by moonlightnvkz on 08.05.17.
//

#pragma once


#include "CardContainer.h"

class TableauStack : public CardContainer{
public:
    TableauStack() {};

    TableauStack(const std::vector<Card> &cards) : CardContainer(cards) {};

    TableauStack(std::vector<Card> &&cards) : CardContainer(std::move(cards)) {}

    virtual ~TableauStack() {};

    using CardContainer::push_back;

    bool push_back(const TableauStack &stack);

    virtual void pop_back() override;

    void pop_tale(size_t amount);

    TableauStack tale(size_t amount);

    virtual bool is_suitable(const Card &card) override;
};