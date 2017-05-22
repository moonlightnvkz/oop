//
// Created by moonlightnvkz on 08.05.17.
//

#pragma once


#include "CardContainer.h"

class TableauStack : public CardContainer{
public:
    TableauStack() {};

    ~TableauStack() { };

    TableauStack(const TableauStack &stack) : CardContainer(stack.cards) { }

    TableauStack(TableauStack &&stack) : CardContainer(std::move(stack.cards)) { }

    TableauStack(std::initializer_list<std::shared_ptr<Card>> list) : CardContainer(list) { }

    TableauStack(const std::vector<std::shared_ptr<Card>> &cards) : CardContainer(cards) {};

    TableauStack(std::vector<std::shared_ptr<Card>> &&cards) : CardContainer(std::move(cards)) {}

    using CardContainer::push_back;

    bool push_back(const TableauStack &stack);

    virtual void pop_back() override;

    void pop_tale(size_t amount);

    TableauStack tale(size_t amount);

    virtual bool is_suitable(const std::shared_ptr<Card> &card) const override;

    TableauStack &operator=(const TableauStack &that);

    TableauStack &operator=(TableauStack &&that);
};