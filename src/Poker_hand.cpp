/*
 * Poker_Hand.cpp
 *
 *  Created on: Apr 22, 2022
 *      Author: kimcd1
 */

#include "Card.h"
#include "Poker_Hand.h"

#include <iostream>
using std::ostream;
using std::cerr;
using std::endl;
using std::cout;

#include <string>
using std::string;

#include <vector>
using std::vector;

#include <algorithm>  // sort, max_element, count, find
using std::sort;
using std::max_element;
using std::find;
using std::greater;

#include <iomanip>  // setw
using std::setw;

using std::count;

#include <map>
using std::map;
using std::multimap;


//bool Poker_Hand::debug_flag = true;

void Poker_Hand::print_method(const std::string& method) const
{
    if(debug_flag)
    {
        cerr << "Poker_Hand::" << method << endl;
    }
}


Poker_Hand::Poker_Hand()
{
    print_method("Poker_Hand()");

    vec_cards.reserve(5);

}


Poker_Hand::~Poker_Hand()
{
    print_method("~Poker_Hand()");
}


void Poker_Hand::push_back(const Card& card)
{
    if(vec_cards.size() < MAX_CARDS)
    {
        // WHY IS THIS CALLING THE CARD'S DEFAULT CONSTRUCTOR???
        cerr << "pushing back a card " << endl;
        vec_cards.push_back(card);
        cerr << "now size is: " << vec_cards.size() << endl;
    }
    // else statement for full?
}


void Poker_Hand::emplace(const Card& card)
{
    if(vec_cards.size() < MAX_CARDS)
    {
        // noticing how i am emplacing_back by returning the card's value and suit
        // try vec_cards.emplace_back(card)... if we do it this way, we are calling hte
        // copy constructor
        vec_cards.emplace_back(card.get_value(), card.get_suit());
    }

    // else statement for full?
}


// consider making this a non-member function. you'd need to make vec_cards accessible to non-member functions to make that work.
vector<string> Poker_Hand::get_pretty_hand() const
{
    vector<string> pretty_hand;
    pretty_hand.reserve(MAX_CARDS);

    for(auto& card : vec_cards)
    {
        pretty_hand.emplace_back(get_pretty_card(card.get_value_enum(), card.get_suit_enum()));
    }

    return pretty_hand;
}

/*
void print_pretty_hand(Poker_Hand& hand)
{
    vector<string> pretty_hand = hand.get_pretty_hand();
    for(auto card : pretty_hand)
    {
        cout << card << " ";
    }
    cout << endl;
}
*/


void Poker_Hand::delete_card_at(int index)
{
    vec_cards.erase(vec_cards.begin() + index);
}


Poker_Hand::Hand_type Poker_Hand::get_hand_type() const
{

    Poker_Hand::Hand_type hand_type;

    multimap<size_t, int, std::greater<size_t>> card_value_frequency_mm;
    card_value_frequency_mm = get_card_value_frequency();

    if(is_same_suits() && is_consecutive(card_value_frequency_mm)) {
        hand_type = Hand_type::STRAIGHT_FLUSH;

    } else if(is_contain_quadruple(card_value_frequency_mm)) {
        hand_type = Hand_type::FOUR_KIND;

    } else if(is_contain_one_pair(card_value_frequency_mm)
              &&
              is_contain_triple(card_value_frequency_mm)) {
        hand_type = Hand_type::FULL_HOUSE;

    } else if(!is_contain_pair(card_value_frequency_mm)
              &&
              is_same_suits()  && !is_consecutive(card_value_frequency_mm)) {  // NEED TO TEST THIS CONDITION
        hand_type = Hand_type::FLUSH;

    } else if (!is_same_suits() && is_consecutive(card_value_frequency_mm)) {
        hand_type = Hand_type::STRAIGHT;

    } else if (!is_contain_pair(card_value_frequency_mm)
               &&
               is_contain_triple(card_value_frequency_mm)) {
        hand_type = Hand_type::THREE_KIND;

    } else if (is_contain_two_pairs(card_value_frequency_mm)) {
        hand_type = Hand_type::TWO_PAIR;

    } else if (is_contain_one_pair(card_value_frequency_mm)
               &&
               !is_contain_triple(card_value_frequency_mm)) {
        hand_type = Hand_type::ONE_PAIR;

    } else
        hand_type = Hand_type::HIGH_CARD;

    return hand_type;
}


std::multimap<size_t, int, std::greater<size_t>> Poker_Hand::get_card_value_frequency() const
{

    // third parameter sorts map by decreasing key order (i.e. higher card value on top)
    map<int, size_t, std::greater<int> > card_value_frequency;

    vector<int> card_values;
    card_values.reserve(5);

    for(auto& card : vec_cards)
    {
        card_values.emplace_back(static_cast<int>(card.get_value_enum()));
    }

    vector<int> unique_cards;  // temporary copy to store unique cards only
    unique_cards = card_values;

    vector<int>::iterator it;

    it = unique(unique_cards.begin(), unique_cards.end());  //
    unique_cards.resize(distance(unique_cards.begin(),it));

    // for each card value in unique_cards, find the frequency in card_values
    for(auto& card_value : unique_cards)
    {
        card_value_frequency.insert(std::pair<int, size_t>(card_value,
                                                           std::count(card_values.begin(), card_values.end(), card_value)));
    }

    // a multimap is like a map except, it may have multiple elements
    // with the same key. additionally, we are going to sort frequency
    // in descending order
    std::multimap< size_t, int, std::greater<size_t> > card_value_frequency_mm;

    for (auto& it : card_value_frequency) {
        card_value_frequency_mm.insert({ it.second, it.first });
    }

    return card_value_frequency_mm;
}


ostream& operator<<(ostream& output, Poker_Hand& hand_object)
{
    // range-based for loop where item (card) in the range (vec_cards) is
    // a reference by const, so as NOT to produce needless copies, which is what
    // happens when you remove "&" and "const". See Card's overloaded operator<<
    // to see how the parameters are defined slightlty differently from usual.
    for(const Card& card : hand_object.vec_cards)
    {
        output << card << " ";
    }

    return output;

}


bool Poker_Hand::is_same_suits() const
{
    for(size_t i = 1; i < MAX_CARDS; ++i)
    {
        if(vec_cards[0].get_suit() != vec_cards[i].get_suit())
        {
            return false;
        }  // end if
    }  // end for
    return true;

}  // end is_same_suits


void print_hand_type(Poker_Hand::Hand_type& hand_type)
{
    switch(hand_type)
    {
        case(Poker_Hand::Hand_type::EMPTY):
            cout << "Not categorized" << endl;
            break;
        case(Poker_Hand::Hand_type::HIGH_CARD):
            cout << "High card" << endl;
            break;
        case(Poker_Hand::Hand_type::ONE_PAIR):
            cout << "One pair" << endl;
            break;
        case(Poker_Hand::Hand_type::TWO_PAIR):
            cout << "Two pair" << endl;
            break;
        case(Poker_Hand::Hand_type::THREE_KIND):
            cout << "Three of a kind" << endl;
            break;
        case(Poker_Hand::Hand_type::STRAIGHT):
            cout << "Straight" << endl;
            break;
        case(Poker_Hand::Hand_type::FLUSH):
            cout << "Flush" << endl;
            break;
        case(Poker_Hand::Hand_type::FULL_HOUSE):
            cout << "Full house" << endl;
            break;
        case(Poker_Hand::Hand_type::FOUR_KIND):
            cout << "Four of a kind" << endl;
            break;
        case(Poker_Hand::Hand_type::STRAIGHT_FLUSH):
            cout << "Straight flush" << endl;
            break;
    }
}
