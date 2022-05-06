/**
 @file Poker_Hand.h
 @brief Five-card draw class definition.
 
 @section DESCRIPTION
 Five_Draw_Table orchestrates a game of five-card draw.
 
 @TODO
 add a remove to remove card from hand.
 add an add to add card to hand.
 do the unique values thing with a map instead of array.
 
 @author Christopher Kim
 */

#ifndef POKER_HAND_H_
#define POKER_HAND_H_

#include"Card.h"

#include <string>
#include <array>
#include <vector>
#include "Card.h"
#include <map>
#include <algorithm>  // max_find

#include <iostream>

class Poker_Hand {

    friend std::ostream& operator<<(std::ostream& output, Poker_Hand& rhs);


public:
    /**
     * Maximum number of cards in a single hand.
     */
    static const size_t MAX_CARDS = 5;

    /**
     * @brief Scoped enumeration of valid hand types in American poker.
     *
     * @detail By using enum, we can order by hierarchy and potentially compare
     * against hand types in a future application. For example,
     * static_cast<int>(Hand_type::STRAIGHT_FLUSH) is greater than
     * static_cast<int>(Hand_type::FOUR_KIND), so we can conclude that one hand
     * ranks higher than the other.
     */
    enum class Hand_type {
        EMPTY = -1,
        HIGH_CARD = 0,
        ONE_PAIR = 1,
        TWO_PAIR = 2,
        THREE_KIND = 3,
        STRAIGHT = 4,
        FLUSH = 5,
        FULL_HOUSE = 6,
        FOUR_KIND = 7,
        STRAIGHT_FLUSH = 8
    };

    /*
     * @brief Default construction to allow for default constructio when game
     * begins.
     */
    Poker_Hand();

    ~Poker_Hand();

    /**
     * @brief Parameterized constructor accepts 5 objects of type Card.
     * @param[in] first_card Reference to Card object first_card.
     * @param[in] second_card Reference to Card object second_card.
     * @param[in] third_card Reference to Card object third_card.
     * @param[in] fourth_card Reference to Card object fourth_card.
     * @param[in] fifth_card Reference to Card object fifth_card.
     */
    Poker_Hand(
         const Card& first_card,
         const Card& second_card,
         const Card& third_card,
         const Card& fourth_card,
         const Card& fifth_card
         );

    void push_back(const Card& card);

    void emplace(const Card& card);

    inline size_t get_quantity() const
    {
        return vec_cards.size();
    }

    std::vector<std::string> get_pretty_hand() const;

    void delete_card_at(int index);


    /*
     * important: this map is <frequency, card_value> pair.
     */
    std::multimap<size_t, int, std::greater<size_t>>
    get_card_value_frequency() const;

    /*
     */
    Poker_Hand::Hand_type get_hand_type() const;



private:
    static bool debug_flag;
    void print_method(const std::string& method) const;
    std::vector<Card> vec_cards;

    /*
     * @brief Test if all Cards in Hand share the same suit.
     * @return True if all Cards in Hand share the same suit. Otherwise, false.
     */
    bool is_same_suits() const;


    /*
     * @brief Test if Cards in Hand are consecutive in value.
     * @return True if consecutive. Otherwise, false.
     */
    inline bool is_consecutive(std::multimap<size_t, int, std::greater<size_t>>& mm) const
    {

        if(mm.size() != 5) return false;

        auto max_it = std::max_element(std::begin(mm), std::end(mm),
                                       [](const auto& l, const auto& r) { return l.second < r.second; });

        int i = 0;

        for(auto& it : mm)
        {
            if(it.second != max_it->second - i)
            {
                return false;
            }
            ++i;
        }

        return true;

    }


    /*
     * @brief Determine whether Hand contains at least a single pair.
     */
    inline bool is_contain_pair(std::multimap<size_t, int, std::greater<size_t>>& mm) const
    {
        return (mm.count(2) > 0) ? true : false;
    }


    /*
     * @brief Tests if Hand contains exactly one pair rather than 2 pairs or no pairs.
     */
    inline bool is_contain_one_pair(std::multimap<size_t, int, std::greater<size_t>>& mm) const
    {
        return (mm.count(2) == 1) ? true : false;
    }


    /*
     * @brief Determine if Hand contains 3 cards of identical value.
     */
    inline bool is_contain_triple(std::multimap<size_t, int, std::greater<size_t>>& mm) const
    {
        return (mm.count(3) == 1) ? true : false;
    }


    /* @brief Determine if Hand contains 4 cards of identical value.
     *
     */
    inline bool is_contain_quadruple(std::multimap<size_t, int, std::greater<size_t>>& mm) const
    {
        return (mm.count(4) == 1) ? true : false;
    }


    /*
     * @brief Test if Hand contains exactly two pairs.
     */
    bool is_contain_two_pairs(std::multimap<size_t, int, std::greater<size_t>>& mm) const
    {
        return (mm.count(2) == 2) ? true : false;
    }

};

void print_pretty_hand(Poker_Hand& hand);

void print_hand_type(Poker_Hand::Hand_type& hand_type);

#endif /* POKER_HAND_H_ */



