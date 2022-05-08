//
//  Player_ABC.h
//  poker-game
//
//  Created by Christopher Kim on 5/7/22.
//  Copyright © 2022 Christopher Kim. All rights reserved.
//

#ifndef Player_ABC_h
#define Player_ABC_h

#include "Poker_Hand.h"



class Player_ABC
{
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
    
    /*
     *
     */ 
    Player_ABC(const unsigned int player_id);
    
    
    /*
     @brief Virtual destructor.
     */
    virtual ~Player_ABC() {}
    
    
    /*
     @brief Add a card to Hand.
     */
    inline void add_card(const Card& card)
    {
        
        print_method("add_card()");
        hand.emplace(card);
    }
    
    
    /*
     @brief
     */
    inline unsigned int get_id() const
    {
        return player_id;
    }
    
    
    inline void print_hand()
    {
        std::cout << hand << std::endl; 
    }
    
    
    /*
     @brief Pure virtual member.
     */
    virtual Player_ABC::Move bet_or_check(int& amount) = 0;
    
    

    
private:
    
    unsigned int player_id;
    
    Poker_Hand hand;
    
    virtual void print_method(const std::string& method) const;
    
};


class Human : public Player_ABC
{
public:
    Human(const unsigned int player_id);
    
    virtual ~Human() {}
    
    /*
     @brief
     */
    virtual Player_ABC::Move bet_or_check(int& amount) override;
    
    /*
     @brief
     */
    
    
private:
    virtual void print_method(const std::string& method) const override;
    
};

/*
class Computer : public Player_ABC
{
public:
    Computer(const unsigned int player_id);
    
    virtual ~Computer() {}
    
private:
    virtual void print_method(const std::string& method) const override;
    
};
*/ 

#endif /* Player_ABC_h */
