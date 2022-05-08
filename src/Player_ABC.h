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
#include <cmath>  // std::nan


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
     @brief Construct a Player abstract base class using player ID.
     
     */ 
    Player_ABC(const unsigned int player_id);
    
    
    /*
     @brief Virtual destructor.
     */
    virtual ~Player_ABC() {}
    
    /*
     @brief Pure virtual I/O interface for paying ante. 
    */
    virtual Player_ABC::Move pay_ante(int ante) = 0; 
    
    
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
    
    
    /*
     @brief
     */
    inline unsigned int get_player_id() const
    {
        return player_id; 
    }
    
    /*
     @brief
     */
    inline void pay_up(int amount)
    {
        
        if(amount > stack)
        {
            if(debug_flag) std::cerr << "Amount exceeds stack." << std::endl;
            
            fold();
        } else
        {
            print_method("pay_up()");
            stack -= amount;
            
            if(debug_flag) std::cerr << "Stack == " << stack << std::endl;
        }
    }
    
    /*
     @brief Fold.
     
     Not sure if I should make this return OR should I create a state that tracks
     the polayer's current state. 
     */
    inline Player_ABC::Move fold()
    {
        
        print_method("fold()");
        
        return Player_ABC::Move::FOLD;
    }

    
private:
    
    unsigned int player_id;
    

    Poker_Hand hand;
    
    
    virtual void print_method(const std::string& method) const;
    
    
    virtual void print_msg(const std::string& method, int val=NAN) const;
    
    
    unsigned int stack{200};  // stack of chips (a.k.a. play money)
    
};


////////////////////////////////////////////////////////////////////////////////
class Human : public Player_ABC
{
public:
    
    /*
     @brief
     */
    Human(const unsigned int player_id);
    
    
    /*
     @brief Drestruct object.
     */
    virtual ~Human() { print_method("Destructor"); }
    
    /*
     @brief
     */
    virtual Player_ABC::Move bet_or_check(int& amount) override;
    
    /*
     @brief
     */
    virtual Player_ABC::Move pay_ante(int amount) override;
    
    
private:
    
    /*
     @brief
     */
    virtual void print_method(const std::string& method) const override;
    
};


////////////////////////////////////////////////////////////////////////////////
class Computer : public Player_ABC
{
public:
    
    /*
     @brief
     */
    Computer(const unsigned int player_id);
    
    /*
     @brief Destruct object.
     */
    virtual ~Computer() { print_method("Destructor"); }
    
    /*
     @brief Strategy for betting/checking.
     */
    virtual Player_ABC::Move bet_or_check(int& amount) override;
    
    /*
     @brief Strategy for paying ante.
     */
    virtual Player_ABC::Move pay_ante(int amount) override;
    
    
private:
    
    virtual void print_method(const std::string& method) const override;
    
};


#endif /* Player_ABC_h */
