//
// Created by moonlightnvkz on 08.05.17.
//

#pragma once

#include <vector>
#include <cstddef>
#include <memory>
#include "Card.h"

class CardContainer {
public:
    CardContainer() { }

    virtual ~CardContainer() { }

    CardContainer(const CardContainer &container) : cards(container.cards) { }

    CardContainer(CardContainer &&container) : cards(std::move(container.cards)) { }

    CardContainer(std::initializer_list<std::shared_ptr<Card>> list) : cards(list) { }

    CardContainer(const std::vector<std::shared_ptr<Card>> &cards) : cards(cards) {};

    CardContainer(std::vector<std::shared_ptr<Card>> &&cards) : cards(std::move(cards)) {}

    const std::vector<std::shared_ptr<Card>> &get_cards() const { return cards; }

    virtual bool push_back(const std::shared_ptr<Card> &card);

    virtual void pop_back();

    std::shared_ptr<Card> get_card(size_t idx_from_back = 0) const;

    size_t size() const { return cards.size(); }

    virtual bool is_suitable(const std::shared_ptr<Card> &card) const;

    CardContainer &operator=(const CardContainer &that);

    CardContainer &operator=(CardContainer &&that);

protected:
    std::vector<std::shared_ptr<Card>> cards;
};


