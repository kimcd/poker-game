#include "Five_Draw_Table.h"

using std::vector;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::cerr;

#include <stdexcept>
using std::invalid_argument;

#include <string>
using std::string;


//bool Five_Draw_Table::debug_flag = true;


Five_Draw_Table::Five_Draw_Table(const size_t num_players)
: players(create_players(num_players)),
dealer(Dealer()),
pot(Pot<int>())
{

}


Five_Draw_Table::Five_Draw_Table()
: players(create_players(prompt_players())),
dealer(Dealer()),
pot(Pot<int>())
{

}


void Five_Draw_Table::print_method(const string& method) const
{
    if(debug_flag)
    {
        cerr << "Five_Draw_Table::" << method << endl;
    }

}

void Five_Draw_Table::print_pot() const
{
    if(debug_flag)
    {
        cerr << "\nCurrent Pot:" << pot.get_value() << endl;
    }

}


vector<Player> Five_Draw_Table::create_players(const size_t num_players) const
{
    print_method("create_players()");

    if(num_players > MAX_PLAYERS)
    {
        throw invalid_argument("This game accepts 2-6 players.");
    }

    vector<Player> players;

    // Reserve and emplace_back will prevent copies of players when vector needs
    // to be reallocated.
    players.reserve(num_players);

    for(int i=0; i < num_players; ++i)
    {
        players.emplace_back(i);
    }

    return players;

}


size_t Five_Draw_Table::prompt_players() const
{
    size_t num_players;

    cout << "How many players: ";
    cin >> num_players;

    if(num_players < MIN_PLAYERS || num_players > MAX_PLAYERS)
    {
        throw invalid_argument("This game accepts 2-6 players.");
    }

    return num_players;
}


void Five_Draw_Table::collect_ante()
{
    // ask people to pay?
    for(Player& player : players)
    {

    	if(player.pay_ante(ANTE) == Player::Move::IN)
    	{
    		pot.add(ANTE);
    	}
    }
}


void Five_Draw_Table::open_betting_round()
{


    int current_player_index = 0;
    //int raise_amount = 0;
    int last_better_index = -1;
    //bool bet_has_been_placed = false;
    int num_players = static_cast<int>(players.size());
    int round = 1;  // captures number of times a player was in play. once around the table would be 1
    int queried_count = 0;  // anytime a player is queried
    int bet_amount = 0;         // this variable has nuance. note here it's declared,
                                // but undefined.
                                // if it flows into the first that means, no one has
                                // placed a bet, rightfully, it should be 0 always.
                                // define to 0 to avoid undefined behavior.
                                //
                                // if it flows into elseif, that means someone HAS
                                // placed a bet. so it contains some value, which is the
                                // previous bet amount. when it's passed to the player,
                                // they will have to match it.
                                //

    while(true)
    {

        current_player_index %= num_players;


        // no one has placed a bet
        if(last_better_index == -1
           &&
           !players[current_player_index].is_folded()
           &&
           round == 1
           )
        {

            print_method("first if");

            //int amount = 0;

            Player::Move decision = players[current_player_index].bet_or_check(bet_amount);

            ++queried_count;

            print_method("decision made");

            if(decision == Player::Move::BET)
            {
                print_method("raised");
                cerr << "Player # bets " << bet_amount << endl;
                last_better_index = current_player_index;
                pot.add(bet_amount);

            } else if(decision == Player::Move::CHECK)
            {
                // do nothing
            } else if(decision == Player::Move::FOLD)
            {
                // do nothing
            }
            // someone has placed a bet and current player is not folded
        } else if (last_better_index != -1
                   &&
                   !players[current_player_index].is_folded()) //&& decision != Player::Move::FOLD)
        {
            print_method("else if");

            // find the index prior to the last_better (preserves the modulo)
            // if 4 players, and last_better == 3, before_last_better == 0
            // int before_last_better_index =
            // abs(last_better_index % num_players - (num_players - 1));

            if(current_player_index == last_better_index)
            {
                cout << "\nBetting is now closed. The pot is " << pot.get_value() << endl;
                print_method("last better");
                break;
            } else
            {
                Player::Move decision = players[current_player_index].raise_or_call(bet_amount);

                ++ queried_count;

                if(decision == Player::Move::RAISE)
                {
                    last_better_index = current_player_index;
                    cerr << "Player # bets " << bet_amount << endl;
                    pot.add(bet_amount);  // we have to add raise amount + already call amount
                    print_pot();

                } else if(decision == Player::Move::CALL)
                {
                    pot.add(bet_amount);    // this value will not have changed,
                                            // but the player calls
                    print_pot();

                } else if(decision == Player::Move::FOLD)
                {
                    // do nothing
                }

            }
        } else
        {
            cout << "\nBetting is now closed. The pot is " << pot.get_value() << endl;
            print_method("break");
            // everyone either called or folded
            break;
        }

        round = round + (queried_count/num_players);

        if(debug_flag)
        {
        	cout << "Round at end: " << round << endl;
        }

        ++current_player_index;

    }  // end while


}


void Five_Draw_Table::discard_round()
{
    // reveal each card to each player and ask them to delete cards
    for(auto& player : players)
    {
        if(!player.is_folded())
        {
            player.discard_round();
        }
    }
}  // end discard_round


vector<size_t> Five_Draw_Table::showdown_round()
{
    // winner id(s) in a vector
    return dealer.rank_hands(players);
}


void Five_Draw_Table::begin_game()
{
    cout << "Welcome to Five-Card Draw Poker." << endl;

    //dealer.show_deck();

    dealer.deal_cards(players);

    collect_ante();

    // ranged-based for loop using a reference to avoid copies of players
    for (auto& player : players)
    {
        player.reveal_cards();
    }

    open_betting_round();

    // what if all players have folded OR ONE PLAYER REMAINING?

    discard_round();

    dealer.replenish_hand(players);

    for (auto& player : players)
    {
        player.reveal_cards();
    }

    // open another betting round
    //open_betting_round();


    vector<size_t> winner_ids = showdown_round();  // though these are player IDs, it is also the index

    vector<Player> temp_players;

    // really don't like this method, but can't find a good way to remove multiple
    // elements from a vector
    for(auto& id_index : winner_ids)
    {
        temp_players.push_back(players[id_index]);
    }

    // distribute money to players
    pot.award_pot(temp_players);

}

