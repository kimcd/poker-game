/*
 * Dealer.cpp
 *
 *  Created on: Apr 22, 2022
 *      Author: kimcd1
 */

#include "Dealer.h"
#include <iostream>
using std::cerr;
using std::endl;
using std::cout;

using std::string;

#include <map>
using std::map;
using std::greater;
using std::multimap;

using std::not_equal_to;

#include <time.h>

#include <algorithm>
using std::adjacent_find;

#include <vector>
using std::vector;

//bool Dealer::debug_flag = true;

typedef multimap<size_t, int, greater<size_t>> card_frequency_mm;


Dealer::Dealer()
: deck(Deck())
{

    print_method("Dealer()");
    shuffle_deck();

}


void Dealer::print_method(const string& method) const
{
    if(debug_flag)
    {
        cerr << "Dealer::" << method << endl;
    }

}


size_t Dealer::compare_strategy(const vector<card_frequency_mm>& vec_mm) const
{
    print_method("compare_strategy()");

    vector<int> temp;

    int it_advance = 0;  // advances the iterator by some amount

    bool draw_flag = false;

    size_t const THRESHOLD = 1000;

    size_t index = THRESHOLD;  // some number beyond the number of players

    do
    {
        for(auto& multi_map : vec_mm)
        {
            auto mm_it = multi_map.begin();
            std::advance(mm_it, it_advance);  // advance iterator by n

            // Store the value in temp vector...
            temp.push_back(mm_it->second);

            if(debug_flag)
            {
            	cerr << " mm_it->second == " << mm_it->second << endl;
            }
        }


        // If they are all equal...
        if(std::adjacent_find(temp.begin(),
                              temp.end(),
                              not_equal_to<>() ) == temp.end())

        {  // ... and they are not the last set of cards...
            if(it_advance  != Poker_Hand::MAX_CARDS - 1)

            {  // ... clear the temp vector and do next iteration.
                temp.clear();

                //  If they are the last set of cards...
            } else if(it_advance  == Poker_Hand::MAX_CARDS - 1)
            {
                //  ... you have reached the end without a winner.
                draw_flag = true;
            }
        } else  // If they aren't all equal, search for the winner.
        {
            auto max = max_element(temp.begin(), temp.end());

            index = distance(temp.begin(), max);

            break;
        }  // else

        ++it_advance ;

    } while(!draw_flag);

    return index;

}


vector<size_t> Dealer::rank_hands(const std::vector<Player> &players) const
{
    print_method("rank_hands()");

    map<unsigned,Poker_Hand::Hand_type> hand_types;


    //  store each player's hand type and player id
    for(auto& i_player : players)
    {
        if(!i_player.is_folded())
        {
            hand_types.insert({i_player.get_number(), i_player.reveal_hand()});
        }
    }

    Poker_Hand::Hand_type max_type = Poker_Hand::Hand_type::EMPTY;

    // Store the highest ranking hand.
    for(auto& it_types : hand_types)
    {
        if(it_types.second > max_type)
        {
            max_type = it_types.second;
            print_hand_type(max_type);
        }
    }

    // if only one person has max, then that person is winner. otherwise,
    // we go into tie-breaker
    vector<size_t> player_id_with_max;


    // Count how many players have the max hand
    for (auto it = hand_types.begin(); it != hand_types.end(); ++it)
        if (it->second == max_type)
        {
            player_id_with_max.push_back(it->first);
            cout << "Player #" << it->first << " has a ";
            print_hand_type(max_type);
        }

    size_t winner_at;

    // If only one player with the max_hand, that's our winner...
    if(player_id_with_max.size() == 1)
    {
        winner_at = 0;

        // ... Otherwise, we go to tie-breaker.
    }  else
    {
        vector<card_frequency_mm> vec_mm;

        // retrieve the card frequencies so you can go to tie-breaker

        // of the players with the max hand...
        for(auto player_index : player_id_with_max)
        {
            multimap<size_t, int, std::greater<size_t>> temp;

            vec_mm.push_back(players[player_index].get_card_value_frequency());

        }

        winner_at = compare_strategy(vec_mm);  // will return the index within
                                               // player_id_with_max (fix this
                                               // so it makes more sense)

    }

    if(winner_at == 1000)
    {
        // every player in players_with_max is a winner
        return player_id_with_max;
    } else
    {
        // return iterator of player ids that are not the winners...
        auto new_end = remove_if(player_id_with_max.begin(),
                                 player_id_with_max.end(),
                                 [player_id_with_max, winner_at](const size_t& val)
                                 {
                                     return val != player_id_with_max[winner_at];
                                 });

        // ... erase all players who are not winners from the vector
        // this will return a vector of with one element
        player_id_with_max.erase(new_end, player_id_with_max.end());

    }

    return player_id_with_max;
}


void Dealer::shuffle_deck()
{

    print_method("shuffle_deck()");

    /*
     -- To shuffle an array a of n elements (indices 0..n-1):
     for i from n−1 downto 1 do
     j ← random integer such that 0 ≤ j ≤ i
     exchange a[j] and a[i]
     */
    unsigned int j;
    unsigned int n = Deck::MAX_CARDS_IN_DECK - 1;

    if(!debug_flag)
    {
        srand(time(NULL));

    } else
    {
        print_method("shuffle_deck() unseeded PRNG");
    }

    for(unsigned int i = n; i > 0; --i)
    {

        j = rand() % i;

        std::swap(deck[j], deck[i]);
    }

}


void Dealer::show_deck()
{

    print_method("show_deck()");

    cout << deck << endl;
}


bool Dealer::is_everyone_full(const vector<Player>& players) const
{

    print_method("is_everyone_full()");

    // Player object is passed by ref to const to prevent copies.
    for(const Player& player : players)
    {
        if(!player.is_hand_full())
        {
            return false;
        }
    }
    return true;
}  // end is_everyone_full


void Dealer::deal_cards(vector<Player>& players)
{
    print_method("deal_cards()");

    while(!is_everyone_full(players))  // while not everyone has a full hand
    {

    for(auto it = players.begin(); it != players.end(); ++it)
    {
        if(!it->is_hand_full())
        {
            it->add_card(deck.get_top_card());
        }
    }  // end for

    }  // end while

}  // end deal_cards



// how do i decide here if i should pass it a vector of players or one player
// at a time and have it loop through multiple players at the NHA (aka five card draw)
void Dealer::replenish_hand(vector<Player>& players)
{
    print_method("replenish_cards()");

    for(auto it = players.begin(); it != players.end(); ++it)
    {
        if(!it->is_folded())
        {
            // until the players hand is full
            while(!it->is_hand_full())
            {
                it->add_card(deck.get_top_card());
            }  // end while

            it->reveal_cards();

        }  // end if !folded
    }  // for

}  // end replenish_hand


