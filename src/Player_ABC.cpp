//
//  Player_ABC.cpp
//  poker-game
//
//  Created by Christopher Kim on 5/7/22.
//  Copyright © 2022 Christopher Kim. All rights reserved.
//

#include "Player_ABC.h"

#include <iostream>
using std::cerr;
using std::endl;
using std::cout;
using std::cin;

#include <string>
using std::string;

#include <stdexcept>
using std::runtime_error;
using std::invalid_argument;


Player_ABC::Player_ABC(unsigned int player_id)
: player_id(player_id)
{
    print_method("Player_ABC()");
}


void Player_ABC::print_method(const string& method) const
{
    
    if(debug_flag)
    {
        cerr << "Player_ABC::" << method << endl;
    }  // end if
}  // end print_method


void Player_ABC::print_msg(const std::string& msg, int val) const
{
    if(debug_flag)
    {
        cerr << msg << val << endl; 
    }  // end if
}  // end print_msg


////////////////////////////////////////////////////////////////////////////////
Human::Human(unsigned int player_id)
: Player_ABC(player_id)
{
    print_method("Human()");
}


void Human::print_method(const string& method) const
{
    if(debug_flag)
    {
        cerr << "Human::" << method << endl;
    }  // end if
}  // end print_method


Player_ABC::Move Human::pay_ante(int amount)
{
    char response;
    
    cout << "Player #" << this->get_player_id()
    << " ante is $" << amount << ". [y/n]" << endl;
    
    cin >> response;
    
    switch(response)
    {
        case 'y': case 'Y':
            pay_up(amount);
            return Player_ABC::Move::IN;
            break;
        case 'n': case 'N':
            return fold();
            break;
        default:
            throw invalid_argument("Unknown enumeration value.");
            break;
    }  // end switch
}  // end pay_ante


Player_ABC::Move Human::bet_or_check(int& amount)
{
    print_method("bet_or_check()");
    
    return Player_ABC::Move::FOLD;
}  // end bet_or_check


////////////////////////////////////////////////////////////////////////////////
Computer::Computer(unsigned int player_id)
: Player_ABC(player_id)
{
    print_method("Computer()");
}


void Computer::print_method(const string& method) const
{
    if(debug_flag)
    {
        cerr << "Computer::" << method << endl;
    }  // end if
}  // end print_method


Player_ABC::Move Computer::bet_or_check(int& amount)
{
    print_method("bet_or_check");
    
    return Player_ABC::Move::FOLD; 
}  // end bet_or_check


Player_ABC::Move Computer::pay_ante(int amount)
{
    
    // always pick yes for now...
    
    pay_up(amount);
    return Player_ABC::Move::FOLD;
}  // end pay_ante
