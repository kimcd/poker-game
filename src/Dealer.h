#ifndef DEALER_H_
#define DEALER_H_

#include "Player.h"
#include "Poker_Hand.h"
#include "Deck.h"
#include <string>
#include <vector>

class Dealer {
public:

    Dealer();

    void deal_cards(std::vector<Player>& players);

    void declare_winner();

    void show_deck();

    static bool debug_flag;

    void replenish_hand(std::vector<Player>& players);

    std::vector<size_t> rank_hands(const std::vector<Player>& players) const;


private:


    Deck deck;

    /*
     * @brief Shuffle the deck.
     *
     * Description
     * Implements the modern version of the Fisher-Yates algorithm produced by
     * Richard Durstenfeld.
     *
     */
    void shuffle_deck();

    void print_method(const std::string& method) const;

    /*
     * Helper function used by the object only.
     */
    bool is_everyone_full(const std::vector<Player>& players) const;

    /*
     *
     */
    size_t compare_strategy(const std::vector<std::multimap<
                            size_t, int, std::greater<size_t>>>& vec_mm) const;

};

//something rank_hands(Hand& hand);


#endif /* DEALER_H_ */
