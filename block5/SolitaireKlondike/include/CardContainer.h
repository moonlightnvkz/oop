//
// Created by moonlightnvkz on 08.05.17.
//

#pragma once

#include <vector>
#include <cstddef>
#include "Card.h"

class CardContainer {
public:
    CardContainer() {};

    CardContainer(const std::vector<Card> &cards) : cards(cards) {};

    CardContainer(std::vector<Card> &&cards) : cards(std::move(cards)) {}

    virtual ~CardContainer() {};

    const std::vector<Card> &get_cards() const { return cards; }

    virtual bool push_back(Card &card);

    virtual bool push_back(Card &&card);

    virtual void pop_back();

    const Card &back() const;

    const Card &peek(size_t idx_from_back);

    size_t size() { return cards.size(); }

    virtual bool is_suitable(const Card &card);

    std::vector<Card> cards;
};


