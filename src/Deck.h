/**
 @file Five_Draw_Table.h
 @brief Five-card draw class definition.
 
 @section DESCRIPTION
 Five_Draw_Table orchestrates a game of five-card draw.
 
 @TODO
 
 
 @author Christopher Kim
 */

#ifndef Deck_h
#define Deck_h

#include "Card.h"
#include <vector>
#include <ostream>
#include <string>


class Deck{

    friend std::ostream& operator<<(std::ostream& output, Deck& deck);


public:
    static const size_t MIN_CARD_VALUE = 2; // 2 = TWO
    static const size_t MAX_CARD_VALUE = 14;  // 14 =  ACE
    static const size_t MAX_CARDS_IN_DECK = 52;
    size_t size() const;


    /*
     * @brief Overloaded subscript operator to iterate over cards.
     */
    Card& operator[] (unsigned int index);

    /*
     * @brief Default construction
     */
    Deck();

    ~Deck();

    std::vector<Card> generate_deck();

    Card get_top_card();

    static bool debug_flag;

private:

    void print_method(const std::string& method) const;
    std::vector<Card> cards;

};


#endif /* Deck_h */
