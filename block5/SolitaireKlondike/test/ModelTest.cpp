//
// Created by moonlightnvkz on 07.05.17.
//

#include <gtest/gtest.h>
#include "../include/Card.h"
#include "../include/CardDeck.h"
#include "../include/FoundationStack.h"
#include "../include/TableauStack.h"
#include "../include/Waste.h"
#include "../include/Foundation.h"
#include "../include/Tableau.h"

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
        std::shared_ptr<Card> card = deck.get_card();
        deck.pop_back();
        ++cards[static_cast<unsigned>(card->get_suit()) * CPS + static_cast<unsigned>(card->get_rank())];
        EXPECT_EQ(card->get_side(), Card::eSide::Back);
    }
    for (const auto c : cards) {
        EXPECT_EQ(c, 1);
    }
}

TEST(FoundationTest, StackAddTest) {
    std::shared_ptr<Card> ace_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Ace);
    std::shared_ptr<Card> king_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::shared_ptr<Card> two_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Two);
    std::shared_ptr<Card> two_cl = std::make_shared<Card>(Card::eSuit::Clubs, Card::eRank::Two);
    FoundationStack stack;
    EXPECT_FALSE(stack.push_back(two_sp));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_FALSE(stack.push_back(king_sp));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.push_back(ace_sp));
    EXPECT_EQ(*stack.get_card(), *ace_sp);
    EXPECT_FALSE(stack.push_back(two_cl));
    EXPECT_EQ(*stack.get_card(), *ace_sp);
    EXPECT_TRUE(stack.push_back(two_sp));
    EXPECT_EQ(*stack.get_card(), *two_sp);
    const std::vector<std::shared_ptr<Card>> &cards = stack.get_cards();
    ASSERT_EQ(cards.size(), 2);
}

TEST(FoundationTest, CompleteTest) {
    Foundation foundation;
    constexpr const unsigned CPS = 13;   // Cards Per Suit
    constexpr const unsigned Suits = 4;
    for (unsigned i = 0; i < Suits; ++i) {
        FoundationStack &stack = foundation.get_stack(i);
        Card::eSuit suit = static_cast<Card::eSuit>(i);
        for (unsigned j = 0; j < CPS; ++j) {
            Card::eRank rank = static_cast<Card::eRank>(j);
            ASSERT_TRUE(stack.push_back(std::make_shared<Card>(suit, rank)));
        }
    }
    EXPECT_TRUE(foundation.is_complete());
}

TEST(TableauTest, StackAddTest) {
    std::shared_ptr<Card> ace_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Ace);
    std::shared_ptr<Card> two_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Two);
    std::shared_ptr<Card> king_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::shared_ptr<Card> queen_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Queen);
    std::shared_ptr<Card> queen_he = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Queen);
    TableauStack stack;
    EXPECT_FALSE(stack.push_back(two_sp));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_FALSE(stack.push_back(ace_sp));
    EXPECT_EQ(stack.size(), 0);
    EXPECT_TRUE(stack.push_back(king_sp));
    EXPECT_EQ(*stack.get_card(), *king_sp);
    EXPECT_FALSE(stack.push_back(queen_sp));
    EXPECT_EQ(*stack.get_card(), *king_sp);
    EXPECT_TRUE(stack.push_back(queen_he));
    EXPECT_EQ(*stack.get_card(), *queen_he);
    const std::vector<std::shared_ptr<Card>> &cards = stack.get_cards();
    ASSERT_EQ(cards.size(), 2);
}

TEST(TableauTest, InitTest) {
    std::array<TableauStack, 7> stacks;
    std::shared_ptr<Card> c1 = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Nine);
    std::shared_ptr<Card> c2 = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Nine);
    std::shared_ptr<Card> c3 = std::make_shared<Card>(Card::eSuit::Clubs, Card::eRank::Nine);
    std::shared_ptr<Card> c4 = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Nine);
    std::shared_ptr<Card> c5 = std::make_shared<Card>(Card::eSuit::Diamonds, Card::eRank::Nine);
    std::vector<std::shared_ptr<Card>> cards{c1, c2, c3, c4, c5};
    for (unsigned i = 0; i < 7; ++i) {
        TableauStack stack(cards);
        stacks.at(i) = std::move(stack);
    }
    Tableau tableau(std::move(stacks));
    for (unsigned i = 0; i < 7; ++i) {
        TableauStack &stack = tableau.stack(i);
        const std::vector<std::shared_ptr<Card>> &sc = stack.get_cards();
        ASSERT_EQ(sc.size(), cards.size());
        size_t size = sc.size();
        for (size_t j = 0; j < size; ++j) {
            EXPECT_EQ(*cards[j], *sc[j]);
            EXPECT_EQ(cards[j]->get_side(), Card::eSide::Back);
        }
    }
}

TEST(TableauTest, StackInitTest) {
    std::shared_ptr<Card> ace_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Ace);
    std::shared_ptr<Card> two_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Two);
    std::shared_ptr<Card> king_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::shared_ptr<Card> queen_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Queen);
    std::shared_ptr<Card> queen_he = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Queen);
    TableauStack stack({two_sp, ace_sp, queen_sp, queen_he, king_sp});
    const auto &cards = stack.get_cards();
    ASSERT_EQ(cards.size(), 5);
    EXPECT_EQ(*stack.get_card(), *king_sp);
    stack.pop_back();
    EXPECT_EQ(*stack.get_card(), *queen_he);
    stack.pop_back();
    EXPECT_EQ(*stack.get_card(), *queen_sp);
    stack.pop_back();
    EXPECT_EQ(*stack.get_card(), *ace_sp);
    stack.pop_back();
    EXPECT_EQ(*stack.get_card(), *two_sp);
    stack.pop_back();
    EXPECT_EQ(stack.size(), 0);
}

TEST(DeckWaste, DeckToWaste) {
    CardDeck deck;
    Waste waste(&deck);

    EXPECT_THROW(deck.move_card_to_waste(), std::logic_error);
    EXPECT_NO_THROW(waste.move_card_to_deck());
    deck.set_waste(&waste);
    const std::shared_ptr<Card> &card = deck.get_card();
    EXPECT_NO_THROW(deck.move_card_to_waste());
    EXPECT_EQ(*waste.get_card(), *card);
    waste.move_card_to_deck();
    EXPECT_EQ(*deck.get_card(), *card);
}

TEST(TableauTest, ConcatTest) {
    std::shared_ptr<Card> king_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::shared_ptr<Card> queen_he = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Queen);
    std::shared_ptr<Card> jack_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Jack);
    std::shared_ptr<Card> ten_he = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Ten);
    std::shared_ptr<Card> jack_he = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Jack);
    std::shared_ptr<Card> ten_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Ten);
    TableauStack a({king_sp, queen_he});
    TableauStack b({jack_he, ten_sp});
    TableauStack c({jack_sp, ten_he});

    EXPECT_FALSE(a.push_back(b));
    EXPECT_EQ(a.get_cards().size(), 2);
    EXPECT_EQ(*a.get_cards()[0], *king_sp);
    EXPECT_EQ(*a.get_cards()[1], *queen_he);

    EXPECT_TRUE(a.push_back(c));
    EXPECT_EQ(a.get_cards().size(), 4);
    EXPECT_EQ(*a.get_cards()[0], *king_sp);
    EXPECT_EQ(*a.get_cards()[1], *queen_he);
    EXPECT_EQ(*a.get_cards()[2], *jack_sp);
    EXPECT_EQ(*a.get_cards()[3], *ten_he);
}

TEST(TableuTest, PopTaleTest) {
    std::shared_ptr<Card> king_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::King);
    std::shared_ptr<Card> queen_he = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Queen);
    std::shared_ptr<Card> jack_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Jack);
    std::shared_ptr<Card> ten_he = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Ten);
    std::shared_ptr<Card> nine_sp = std::make_shared<Card>(Card::eSuit::Spades, Card::eRank::Nine);
    std::shared_ptr<Card> eight_he = std::make_shared<Card>(Card::eSuit::Hearts, Card::eRank::Eight);
    TableauStack a({king_sp, queen_he, jack_sp,
                    ten_he, nine_sp, eight_he});
    TableauStack tale = a.tale(1);
    a.pop_tale(1);
    {
        const std::vector<std::shared_ptr<Card>> &cards = tale.get_cards();
        ASSERT_EQ(cards.size(), 1);
        EXPECT_EQ(*cards[0], *eight_he);
        a.push_back(eight_he);
    }
    tale = a.tale(2);
    a.pop_tale(2);
    {
        const std::vector<std::shared_ptr<Card>> &cards = tale.get_cards();
        ASSERT_EQ(cards.size(), 2);
        EXPECT_EQ(*cards[0], *nine_sp);
        EXPECT_EQ(*cards[1], *eight_he);
        a.push_back(nine_sp);
        a.push_back(eight_he);
    }
    tale = a.tale(4);
    a.pop_tale(4);
    {
        const std::vector<std::shared_ptr<Card>> &cards = tale.get_cards();
        ASSERT_EQ(cards.size(), 4);
        EXPECT_EQ(*cards[0], *jack_sp);
        EXPECT_EQ(*cards[1], *ten_he);
        EXPECT_EQ(*cards[2], *nine_sp);
        EXPECT_EQ(*cards[3], *eight_he);
    }
}