//
// Created by moonlightnvkz on 07.05.17.
//

#include <gtest/gtest.h>
#include "../include/model/Card.h"
#include "../include/model/CardDeck.h"
#include "../include/model/FoundationStack.h"
#include "../include/model/TableauStack.h"
#include "../include/model/Waste.h"

bool operator==(const Card &a, const Card &b) {
    return a.get_suit() == b.get_suit() &&
           a.get_rank() == b.get_rank();
}

TEST(CardDeckTest, IntegrityTest) {
    CardDeck deck;
    constexpr const unsigned Amount = 52;
    constexpr const unsigned CPS = 13;   // Cards Per Suit
    std::vector<unsigned> cards(Amount, 0);
    for (unsigned i = 0; i < Amount; ++i) {
        const Card &card = deck.back();
        deck.pop_back();
        ++cards[static_cast<unsigned>(card.get_suit()) * CPS + static_cast<unsigned>(card.get_rank())];
        EXPECT_EQ(card.get_side(), Card::eSide::Back);
    }
    EXPECT_THROW(deck.back(), std::logic_error);
    EXPECT_NO_THROW(deck.pop_back());
    EXPECT_THROW(deck.peek(0), std::logic_error);
    for (const auto c : cards) {
        EXPECT_EQ(c, 1);
    }
}

TEST(FoundationTest, StackAddTest) {
    Card ace_sp(Card::eSuit::Spades, Card::eRank::Ace);
    Card king_sp(Card::eSuit::Spades, Card::eRank::King);
    Card two_sp(Card::eSuit::Spades, Card::eRank::Two);
    Card two_cl(Card::eSuit::Clubs, Card::eRank::Two);
    FoundationStack stack;
    EXPECT_FALSE(stack.push_back(two_sp));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_FALSE(stack.push_back(king_sp));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.push_back(ace_sp));
    EXPECT_EQ(stack.back(), ace_sp);
    EXPECT_FALSE(stack.push_back(two_cl));
    EXPECT_EQ(stack.back(), ace_sp);
    EXPECT_TRUE(stack.push_back(two_sp));
    EXPECT_EQ(stack.back(), two_sp);
    const std::vector<Card> &cards = stack.get_cards();
    ASSERT_EQ(cards.size(), 2);
}

TEST(TableauTest, StackAddTest) {
    Card ace_sp(Card::eSuit::Spades, Card::eRank::Ace);
    Card two_sp(Card::eSuit::Spades, Card::eRank::Two);
    Card king_sp(Card::eSuit::Spades, Card::eRank::King);
    Card queen_sp(Card::eSuit::Spades, Card::eRank::Queen);
    Card queen_he(Card::eSuit::Hearts, Card::eRank::Queen);
    TableauStack stack;
    EXPECT_FALSE(stack.push_back(two_sp));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_FALSE(stack.push_back(ace_sp));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.push_back(king_sp));
    EXPECT_EQ(stack.back(), king_sp);
    EXPECT_FALSE(stack.push_back(queen_sp));
    EXPECT_EQ(stack.back(), king_sp);
    EXPECT_TRUE(stack.push_back(queen_he));
    EXPECT_EQ(stack.back(), queen_he);
    const std::vector<Card> &cards = stack.get_cards();
    ASSERT_EQ(cards.size(), 2);
}

TEST(TableauTest, StackInitTest) {
    Card ace_sp(Card::eSuit::Spades, Card::eRank::Ace);
    Card two_sp(Card::eSuit::Spades, Card::eRank::Two);
    Card king_sp(Card::eSuit::Spades, Card::eRank::King);
    Card queen_sp(Card::eSuit::Spades, Card::eRank::Queen);
    Card queen_he(Card::eSuit::Hearts, Card::eRank::Queen);
    TableauStack stack({two_sp, ace_sp, queen_sp, queen_he, king_sp});
    const auto &cards = stack.get_cards();
    ASSERT_EQ(cards.size(), 5);
    EXPECT_EQ(stack.back(), king_sp);
    stack.pop_back();
    EXPECT_EQ(stack.back(), queen_he);
    stack.pop_back();
    EXPECT_EQ(stack.back(), queen_sp);
    stack.pop_back();
    EXPECT_EQ(stack.back(), ace_sp);
    stack.pop_back();
    EXPECT_EQ(stack.back(), two_sp);
    stack.pop_back();
    EXPECT_EQ(stack.size(), 0);
}

TEST(DeckWaste, DeckToWaste) {
    CardDeck deck;
    Waste waste(&deck);

    EXPECT_THROW(deck.move_card_to_waste(), std::logic_error);
    EXPECT_NO_THROW(waste.move_card_to_deck());
    deck.set_waste(&waste);
    const Card &card = deck.back();
    EXPECT_NO_THROW(deck.move_card_to_waste());
    EXPECT_EQ(waste.back(), card);
    waste.move_card_to_deck();
    EXPECT_EQ(deck.back(), card);
    EXPECT_THROW(waste.back(), std::logic_error);
}

TEST(TableauTest, ConcatTest) {
    Card king_sp(Card::eSuit::Spades, Card::eRank::King);
    Card queen_he(Card::eSuit::Hearts, Card::eRank::Queen);
    Card jack_sp(Card::eSuit::Spades, Card::eRank::Jack);
    Card ten_he(Card::eSuit::Hearts, Card::eRank::Ten);
    Card jack_he(Card::eSuit::Hearts, Card::eRank::Jack);
    Card ten_sp(Card::eSuit::Spades, Card::eRank::Ten);
    TableauStack a({king_sp, queen_he});
    TableauStack b({jack_he, ten_sp});
    TableauStack c({jack_sp, ten_he});

    EXPECT_FALSE(a.push_back(b));
    EXPECT_EQ(a.get_cards().size(), 2);
    EXPECT_EQ(a.get_cards()[0], king_sp);
    EXPECT_EQ(a.get_cards()[1], queen_he);

    EXPECT_TRUE(a.push_back(c));
    EXPECT_EQ(a.get_cards().size(), 4);
    EXPECT_EQ(a.get_cards()[0], king_sp);
    EXPECT_EQ(a.get_cards()[1], queen_he);
    EXPECT_EQ(a.get_cards()[2], jack_sp);
    EXPECT_EQ(a.get_cards()[3], ten_he);
}

TEST(TableuTest, PopTaleTest) {
    Card king_sp(Card::eSuit::Spades, Card::eRank::King);
    Card queen_he(Card::eSuit::Hearts, Card::eRank::Queen);
    Card jack_sp(Card::eSuit::Spades, Card::eRank::Jack);
    Card ten_he(Card::eSuit::Hearts, Card::eRank::Ten);
    Card nine_sp(Card::eSuit::Spades, Card::eRank::Nine);
    Card eight_he(Card::eSuit::Hearts, Card::eRank::Eight);
    TableauStack a({king_sp, queen_he, jack_sp, ten_he, nine_sp, eight_he});
    TableauStack tale = a.tale(1);
    a.pop_tale(1);
    {
        const std::vector<Card> &cards = tale.get_cards();
        ASSERT_EQ(cards.size(), 1);
        EXPECT_EQ(cards[0], eight_he);
        a.push_back(eight_he);
    }
    tale = a.tale(2);
    a.pop_tale(2);
    {
        const std::vector<Card> &cards = tale.get_cards();
        ASSERT_EQ(cards.size(), 2);
        EXPECT_EQ(cards[0], nine_sp);
        EXPECT_EQ(cards[1], eight_he);
        a.push_back(nine_sp);
        a.push_back(eight_he);
    }
    tale = a.tale(4);
    a.pop_tale(4);
    {
        const std::vector<Card> &cards = tale.get_cards();
        ASSERT_EQ(cards.size(), 4);
        EXPECT_EQ(cards[0], jack_sp);
        EXPECT_EQ(cards[1], ten_he);
        EXPECT_EQ(cards[2], nine_sp);
        EXPECT_EQ(cards[3], eight_he);
    }
}