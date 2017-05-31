//
// Created by moonlightnvkz on 08.05.17.
//

#include <cstddef>
#include "../include/TableauStack.h"

bool TableauStack::push_back(TableauStack &&stack) {
    if (size() > 0 && is_suitable(stack.cards[0].get())) {
        for (auto &c : stack.cards) {
            this->cards.push_back(std::move(c));
        }
        return true;
    }
    return false;
}

bool TableauStack::is_suitable(const Card *card) const {
    const Card *top = peek_card();
    if (card == nullptr) {
        return true;
    }
    if (top == nullptr) {
        return card->get_rank() == Card::eRank::King;
    }
    return static_cast<size_t>(top->get_rank()) == static_cast<size_t>(card->get_rank()) + 1
           && top->is_black() != card->is_black();
}

void TableauStack::pop_tale(size_t amount) {
    size_t size = cards.size();
    if (amount > size) {
        amount = size;
    }
    for (size_t i = 0; i < amount; ++i) {
        cards.pop_back();
    }
}

void TableauStack::pop_back() {
    CardContainer::pop_back();
    if (!cards.empty()) {
        cards.back()->set_side(Card::eSide::Face);
    }
}

TableauStack TableauStack::tale(size_t amount) {
    size_t size = cards.size();
    if (amount > size) {
        amount = size;
    }
    std::vector<std::unique_ptr<Card>> tale;
    for (auto i = cards.end() - amount; i < cards.end(); ++i) {
        tale.push_back(std::move(*i));
    }
    return std::move(TableauStack(std::move(tale)));
}

TableauStack &TableauStack::operator=(TableauStack &&that) {
    if (this != &that) {
        this->cards = std::move(that.cards);
    }
    return *this;
}
