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

    CardContainer(CardContainer &&container) : cards(std::move(container.cards)) { }

    CardContainer(std::vector<std::unique_ptr<Card>> &&cards) : cards(std::move(cards)) {}

    const std::vector<std::unique_ptr<Card>> &get_cards() const { return cards; }

    virtual bool push_back(std::unique_ptr<Card> &&card);

    std::unique_ptr<Card> back();

    virtual void pop_back();

    const Card *peek_card(size_t idx_from_back = 0) const;

    size_t size() const { return cards.size(); }

    virtual bool is_suitable(const Card *card) const;

    CardContainer &operator=(CardContainer &&that);

protected:
    std::vector<std::unique_ptr<Card>> cards;
};


