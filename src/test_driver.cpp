#include "Deck.h"
#include "Pot.h"
#include "Five_Draw_Table.h"
#include "SCRATCHPAD.h"
#include "Poker_Hand.h"
#include "Dealer.h"
#include "Player_ABC.h"

#include <iostream>
using std::cerr;
using std::endl;
using std::cout;

#include <stdexcept>
using std::invalid_argument;


// test correct exception is thrown when incorrect
bool test_player_exception(const size_t out_of_range)
{
    try
    {
        Five_Draw_Table game(out_of_range);
        cerr << "Five_Draw_Table("
             << out_of_range << ") failed to throw and exception." << endl;
        return false;
    }
    catch(invalid_argument &e)
    {
        // cerr << "Five_Draw_Table("
        // << out_of_range << ") threw exception: "
        // << e.what() << endl;
        return true;
    }
}


bool test_player_prompt_exception()
{
    try
    {
        // default constructor
        Five_Draw_Table game;
        cerr << "Five_Draw_Table(";
        return false;
    }
    catch(invalid_argument &e)
    {
        return true;
    }
}




void test_all_exceptions()
{
    test_player_exception(7);

    test_player_prompt_exception();
}


void run_poker_game()
{
    Five_Draw_Table game;
    game.begin_game();
}

void run_test_player_abc()
{
    test_player_abc();
    
}

bool Player_ABC::debug_flag = true;
bool Card::debug_flag = false;
bool Deck::debug_flag = false;
bool Player::debug_flag = false;
bool Dealer::debug_flag = false;
bool Five_Draw_Table::debug_flag = false;
bool Poker_Hand::debug_flag = false;

int main(int argc, const char * argv[]) {
    //run_test_player_abc();
    
    test_player_ante();
    /*

    test_card_unique();
    test_pot();
    deck_design();
    test_unseeded_rand();
    shuffle_design();
    test_deck_subscript();
     test_all_exceptions();
     */

    //test_unique_values_map();
    //test_card_unique_values();
    //test_hand_typer();

    //test_multi_map_tie_breaker();

    //rank_design();
    //remove_vector();
    //run_poker_game();
    //selection_design();
    //raise_design();

    //test_poker_hand_push_back();

    //test_poker_hand_emplace();
    //test_emplace_vector();

    //make_move_design();

    return 0;

}

