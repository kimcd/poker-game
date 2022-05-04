#include "Deck.h"

#include <iostream>
using std::cerr;
using std::endl;

Deck::Deck()
:cards(generate_deck())
{
    print_method("Deck()");

}

Deck::~Deck()
{
    print_method("~Deck()");
}

// maybe this isn't the most optimized way to produce a temp vector and pass?
std::vector<Card> Deck::generate_deck()
{
    print_method("generate_deck()");

    std::vector<Card> deck;

    // reserve to prevent copies when resizing
    deck.reserve(52);

    // iterate over indices of Card::Value from 2 through Ace
    for(int i_val = MIN_CARD_VALUE; i_val <= MAX_CARD_VALUE; ++i_val)
    {
        // iterate over indices of Card::Suit from Heart to Diamond
        for(int i_suit = 1; i_suit <=4; ++i_suit)
        {
            if(debug_flag) cerr << i_val << " " << i_suit << endl;
            // This creates a Card object, then copies and pushes it back to deck.
            // https://zpjiang.me/2018/08/08/Copy-Constructor-and-std-vector-emplace-back/
            //deck.push_back(Card(int_to_card_value(i_val), int_to_card_suit(i_suit)));

            // This does some weird copies in int_to_card_value().
            //deck.emplace_back(int_to_card_value(i_val), int_to_card_suit(i_suit));

            // This creates a Card object in the deck.
            deck.emplace_back(i_val, i_suit);
        }

    }

    return deck;

}


Card& Deck::operator[] (unsigned int index)
{
    return cards[index];
}

size_t Deck::size() const
{
    return cards.size();
}


Card Deck::get_top_card()
{
    print_method("top_card()");

    // copy to temporary
    // when erasing from anywhere other than last position, it will
    // resize the vector.
    Card top_card = *(cards.end()-1);  // dereference a pointer. copy temp
    cards.erase(cards.end()-1);

    // remove from deck
    // Card top_card = cards[0];
    //cards.erase(cards.begin(), cards.begin()+1);  // i think this should be erase(cards.begin())

    // deal out card
    return top_card;

}

std::ostream& operator<<(std::ostream& output, Deck& deck)
{

    for(const Card& card : deck.cards)
    {
        output << card << '\n';
    }

    return output;

}

void Deck::print_method(const std::string& method) const
{
    if(debug_flag)
    {
        cerr << "Deck::" << method << endl;
    }

}

