/**
 @file Player.h
 @brief Player class definition.
 
 @section DESCRIPTION
 
 @TODO
 Player identification. Does it matter?
 Players own hands.
 Players need to bet.
 Players need to trade cards.
 Players need to accept new cards?
 Players need to
 
 @author Christopher Kim
 */



#ifndef Player_h
#define Player_h

#include "Poker_Hand.h"
#include <string>

class Player {

public:

    static bool debug_flag;

    enum class Move
    {
        NOTYET = -1,
        IN,
        BET,
        FOLD,
        CHECK,
        CALL,
        RAISE
        //,STANDPAT
    };


    Player(size_t number);

    void add_card(const Card& card);



    ~Player();

    //virtual void betting_strategy() = 0;

    //virtual void play_strategy();


    void reveal_cards();


    inline bool is_hand_full() const
    {
        return (hand.get_quantity() < 5) ? false : true;
    }


    Player::Move pay_ante(int amount);


    Player::Move bet_or_check(int& amount);


    Player::Move raise_or_call(int& amount);


    inline bool is_folded() const
    {
        return fold_flag;
    };


    bool fold_flag{false};


    void discard_round();


    inline Poker_Hand::Hand_type reveal_hand() const
    {
        return hand.get_hand_type();
    }


    inline std::multimap<size_t, int, std::greater<size_t>>
    get_card_value_frequency() const
    {
        return hand.get_card_value_frequency();
    }


    inline size_t get_number() const
    {
        return player_number;

    }


    inline void add_money(size_t amount)
    {
        stack += amount;
    }


    inline void debit_money(size_t amount)
    {
        stack -= amount;
    }


private:

    void print_method(const std::string& method) const;

    /*
     * @brief Display hand to screen and accept a selection.
     */
    void hand_display_selection_mode();

    size_t player_number;

    Poker_Hand hand;

    int stack{100};

    Player::Move fold();
    Player::Move bet(int & amount);
    Player::Move raise(int& amount);
    Player::Move call(int& amount);


    //void make_bet() const;

    void call();


    void check();


    void discard(int input);


    void allin(); // would call raise
};

#endif /* Player_h */
