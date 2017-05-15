//
// Created by moonlightnvkz on 07.05.17.
//

#pragma once


class Card {
public:
    enum class eSuit {
        Hearts,
        Clubs,
        Diamonds,
        Spades
    };

    enum class eRank {
        Ace,
        Two,
        Three,
        Four,
        Five,
        Six,
        Seven,
        Eight,
        Nine,
        Ten,
        Jack,
        Queen,
        King
    };

    enum class eSide {
        Back,
        Face
    };

    Card(eSuit suit, eRank rank, eSide side = eSide::Back) : suit(suit), rank(rank), side(side){ }

    eSuit get_suit() const { return suit; }

    eRank get_rank() const { return rank; }

    eSide get_side() const { return side; }

    void set_side(eSide side) { this->side = side; }

    void flip() { side = side == eSide::Back ? eSide::Face : eSide::Back; }

    bool is_black() const { return suit == eSuit::Clubs || suit == eSuit::Spades; }
private:
    eSuit suit;
    eRank rank;
    eSide side;
};


