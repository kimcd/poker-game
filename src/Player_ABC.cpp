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

#include <string>
using std::string;


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
    }
    
}


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
    }

}


Player_ABC::Move Human::bet_or_check(int& amount)
{
    print_method("bet_or_check()");
    
    return Player_ABC::Move::FOLD;
}

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
    }
}

Player_ABC::Move Computer::bet_or_check(int& amount)
{
    print_method("bet_or_check");
    
    return Player_ABC::Move::FOLD; 
}
