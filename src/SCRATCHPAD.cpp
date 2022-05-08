//
//  SCRATCHPAD.cpp
//  module_12
//
//  Created by Christopher Kim on 4/22/22.
//  Copyright � 2022 Christopher Kim. All rights reserved.
//

#include "SCRATCHPAD.h"
#include "Poker_Hand.h"
#include "Player.h"
#include "Deck.h"
#include "Player_ABC.h"


#include <map>
using std::map;
using std::multimap;

#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
using std::cin;

#include "Card.h"

#include "Dealer.h"

#include <vector>
using std::vector;

#include "Deck.h"

#include <algorithm>
using std::sort;

#include <iterator>
using std::distance;

#include "Pot.h"

#include <iomanip>
using std::setw;

using std::remove_if;

#include <string>
using std::string;

void print_map(map<int, int>& map_obj)
{
    map<int, int>::iterator itr;
    cout << "\nThe map gquiz1 is : \n";
    cout << "\tKEY\tELEMENT\n";
    for (itr = map_obj.begin(); itr != map_obj.end(); ++itr) {
        cout << '\t' << itr->first << '\t' << itr->second
        << '\n';
    }
    cout << endl;
}

void print_map(map<int, size_t>& map_obj)
{
    map<int, size_t>::iterator itr;
    cout << "VALUE\tFREQUENCY\n";
    for (itr = map_obj.begin(); itr != map_obj.end(); ++itr) {
        cout << itr->first << '\t' << '\t' << itr->second
        << '\n';
    }
    cout << endl;
}

void print_map(map<int, size_t, std::greater<int> >& map_obj)
{
    map<int, size_t>::iterator itr;
    cout << "VALUE\tFREQUENCY\n";
    for (itr = map_obj.begin(); itr != map_obj.end(); ++itr) {
        cout << itr->first << '\t' << '\t' << itr->second
        << '\n';
    }
    cout << endl;
}


void print_vector(const vector<int>& vec)
{
    for (auto ele : vec)
    {
        cerr << ele << " ";
    }

    cerr << endl;
}

// design of a map that contains key value pairs of keys that represent card
// values and their frequency of occurrence
void test_unique_values_map()
{
    map<int, int> card_values;
    card_values.insert(std::pair<int,int> (1, 40));
    card_values.insert(std::pair<int, int> (2, 50));

    print_map(card_values);

    // 1. get a vector and extract the unique values
    vector<int> v;
    v = {8, 2, 3, 6, 4, 5, 6, 7, 8, 3, 8, 8, 1};

    vector<int> v_unique = v;  // copy

    sort(v_unique.begin(), v_unique.end());
    vector<int>::iterator it;

    it = unique(v_unique.begin(), v_unique.end());  //  only grab unique values
    v_unique.resize(distance(v_unique.begin(),it));

    cerr << "values of v: ";
    print_vector(v);

    cerr << "value of v_unique: ";
    print_vector(v_unique);

    // 2. count up frequency of each unique value and insert into a map
    vector<size_t> frequency;
    map<int, size_t> card_value_frequency;

    for(auto ele : v_unique)
    {
        size_t f;
        f = std::count(v.begin(), v.end(), ele);
        frequency.push_back(f);
        cerr << ele << ": " << f << endl;

        card_value_frequency.insert(std::pair<int, size_t>(ele, f));
    }
    print_map(card_value_frequency);

}

void test_card_unique_values()
{
    map<int, size_t, std::greater<int> > card_value_frequency;
    //card_value_frequency.insert(std::pair<int,int> (1, 40));
    //card_value_frequency.insert(std::pair<int, int> (2, 50));

    vector<int> card_values;
    card_values.reserve(5);

    vector<int> unique_cards;
    unique_cards.reserve(5);

    vector<Card> vec_cards;
    vec_cards.reserve(5);
    vec_cards.emplace_back(6,1);
    vec_cards.emplace_back(4,3);
    vec_cards.emplace_back(5,1);
    vec_cards.emplace_back(7,2);
    vec_cards.emplace_back(3,2);


    for(auto& card : vec_cards)
    {
        card_values.emplace_back(static_cast<int>(card.get_value_enum()));
    }

    //sort(card_values.begin(), card_values.end());

    print_vector(card_values);

    unique_cards = card_values;

    vector<int>::iterator it;

    it = unique(unique_cards.begin(), unique_cards.end());  //
    unique_cards.resize(distance(unique_cards.begin(),it));

    print_vector(unique_cards);

    // 2. count up frequency of each unique value and insert into a map
    //map<int, size_t> card_value_frequency;

    for(auto& ele : unique_cards)
    {
        card_value_frequency.insert(
                                    std::pair<int, size_t>(ele,
                                                           std::count(card_values.begin(), card_values.end(), ele)));
    }

    print_map(card_value_frequency);


    std::multimap< size_t, int, std::greater<size_t> > MM;

    for (auto& it : card_value_frequency) {
        MM.insert({ it.second, it.first });
    }

    for (auto& it : MM) {
        cout << it.second << ' '
        << it.first << endl;
    }

    for (auto& it : MM) {
        string result;
        result = (it.first == 2) ? "pair" : "no-pair";
        cout << result;
    }

    cout << "2 exists " << MM.count(2) << endl;

    cout << "size: " <<  MM.size() << endl;

    auto max_it = std::max_element(std::begin(MM), std::end(MM),
                               [](const auto& l, const auto& r) { return l.second < r.second; });

    cout << max_it->second << endl;
    cout << max_it->second + 1 << endl;

    int i = 0;

    for(auto& it : MM)
    {
        if(it.second == max_it->second - i)
        {
            cout << "yes" << endl;
        }
        ++i;
    }


}

void print_multimap(std::multimap< size_t, int, std::greater<size_t> >& mm)
{
    for (auto& it : mm) {
        cout << it.first << ' '
        << it.second << endl;
    }
}


void test_multi_map_tie_breaker()
{

    vector<std::multimap< size_t, int, std::greater<size_t>>> vector_MM;
    std::multimap< size_t, int, std::greater<size_t> > MM;
    MM.insert({1, 7});
    MM.insert({1, 6});
    MM.insert({1, 5});
    MM.insert({1, 4});
    MM.insert({1, 3});
    print_multimap(MM);
    vector_MM.push_back(MM);

    std::multimap< size_t, int, std::greater<size_t> > MM2;
    MM2.insert({1, 8});
    MM2.insert({1, 6});
    MM2.insert({1, 5});
    MM2.insert({1, 4});
    MM2.insert({1, 3});
    print_multimap(MM2);
    vector_MM.push_back(MM2);

    std::multimap< size_t, int, std::greater<size_t> > MM3;
    MM3.insert({1, 7});  // 0
    MM3.insert({1, 6});  // 1
    MM3.insert({1, 5});  // 2
    MM3.insert({1, 4});  // 3
    MM3.insert({1, 3});  // 4
    print_multimap(MM3);
    vector_MM.push_back(MM3);

    vector<int> temp;

    int n = 0;

    bool draw_flag = false;

    do
    {
        for(auto& multi_map : vector_MM)
        {
            auto ite = multi_map.begin();
            std::advance(ite, n);

            temp.push_back(ite->second);

            cout << " ite->second == " << ite->second << endl;

        }
        print_vector(temp);
        cout << endl;
        //++n;

        // if they are all equal, continue
        if(std::adjacent_find(temp.begin(), temp.end(), std::not_equal_to<>() ) == temp.end())
        {
            if(n != 5-1)
            {
                temp.clear();
                //continue;
            } else if(n == 5-1)
            {
                cout << "this game is a draw" << endl;
                draw_flag = true;
            }
        } else  // if they aren't equal search for the winner
        {
            auto max = max_element(temp.begin(), temp.end());

            size_t index = distance(temp.begin(), max);

            cout << "Player #" << index << " has the winning hand. " << endl;

            break;
        }  // else

        ++n;

    } while(!draw_flag);

    cout << "here's vector before stop on loop " << n << endl;
    print_vector(temp);



}

void rank_design()
{
    //vector<Poker_Hand::Hand_type> hand_types;
    map<unsigned,Poker_Hand::Hand_type> hand_types;

    hand_types.insert({0, Poker_Hand::Hand_type::STRAIGHT_FLUSH});
    hand_types.insert({1, Poker_Hand::Hand_type::FLUSH});
    hand_types.insert({2, Poker_Hand::Hand_type::EMPTY});
    hand_types.insert({3, Poker_Hand::Hand_type::STRAIGHT_FLUSH});
    hand_types.insert({4, Poker_Hand::Hand_type::FLUSH});


    for(auto& it_types : hand_types)
    {
        cout << "Player# " << it_types.first << " has ";
        print_hand_type(it_types.second);
    }

    Poker_Hand::Hand_type max_type = Poker_Hand::Hand_type::EMPTY;

    for(auto& it_types : hand_types)
    {
        if(static_cast<int>(it_types.second) > static_cast<int>(max_type))
        {
            max_type = it_types.second;
            print_hand_type(max_type);
        }
    }

    // if only one person has max, then that person is winner. otherwise, we go into comparison
    vector<unsigned> players_with_max;

    for (auto it = hand_types.begin(); it != hand_types.end(); ++it)
        if (it->second == max_type)
        {
            players_with_max.push_back(it->first);
            cout << "Player #" << it->first << " has a ";
            print_hand_type(max_type);
        }

    if(players_with_max.size() > 1)
    {


    }
}



void test_card_unique()
{
    vector<Card> cards;

    cards.push_back(Card(4,1));  // four of hearts
    cards.push_back(Card(4,2));

    for(Card card : cards)
    {
        cerr << card << '\n';
    }

}

void test_card()
{
    // this is just to make sure Card construction always works throughout development.

    Card my_card(Card::Value::ACE, Card::Suit::H);
    cout << "my_card: " << my_card;
}

void test_deck()
{
    // this is just to make sure Deck construction always works throughout development.
    Deck my_deck;

    cout << my_deck;


}


void deck_design()
{
    std::vector<Card> deck;

    // iterate an array of values from 1 through 14
    for(int i_val = 2; i_val <= 14; ++i_val)
        for(int i_suit = 1; i_suit <=4; ++i_suit)
        {
            deck.push_back(Card(int_to_card_value(i_val),
                                int_to_card_suit(i_suit)));
        }

    print_deck(deck);

}

void print_deck(std::vector<Card>& deck)
{
    for(auto card : deck)
    {
        cout << card << endl;
    }
}

void iter_enum()
{
    Card::Value x = Card::Value::ACE;

    cout << static_cast<int>(x) << endl;

    int y = 3;

    Card::Value hello = static_cast<Card::Value>(y);

    cout << convert_enum_card_value_to_string(hello);

    cout << endl;

}

void test_unseeded_rand()
{
    // from page 218 of textbook
    for(unsigned int counter = 1; counter <= 20; ++counter)
    {
        cout << setw(10) << (1 + rand() % 52);

        if(counter % 5 == 0)
        {
            cout << '\n';
        }
    }
}

void test_pot()
{
    Pot<int> int_pot;
    int_pot.add(3);
    int_pot.add(123.43);
    int_pot.add(1343.34);
    cerr << "int_pot: " << int_pot << endl;

    Pot<double> dbl_pot;
    dbl_pot.add(100.23);
    cerr << "dbl_pot == " << dbl_pot << endl;

    Pot<size_t> size_t_pot;
    size_t_pot.add(100.23);
    cerr << "size_t_pot == " << size_t_pot << endl;

}

void test_hand_typer()
{
    // SHDC
    //array<string, 5> hand1 = {"Tc", "9c", "8c", "7c", "6c"};
    //array<string, 5> hand2 = {"8h", "7h", "6h", "5h", "4h"};

    Poker_Hand my_hand;
    my_hand.emplace(Card(10,4));
    my_hand.emplace(Card(9,4));
    my_hand.emplace(Card(8,4));
    my_hand.emplace(Card(7,4));
    my_hand.emplace(Card(6,4));

    Poker_Hand::Hand_type type;

    type = my_hand.get_hand_type();

    //cout << "\n" << static_cast<int>(type) << endl;

    print_hand_type(type);
}

void shuffle_design()
{
    vector<int> vec;

    for(int i = 1; i <= 52; ++i)
    {
        vec.push_back(i);
    }

    cout << "vector size" << vec.size() << endl;
    print_vector(vec);

    /*
     -- To shuffle an array a of n elements (indices 0..n-1):
     for i from n1 downto 1 do
     j  random integer such that 0  j  i
     exchange a[j] and a[i]
     */
    unsigned int j;
    unsigned int n = 51;

    for(unsigned int i = n; i > 0; --i)
    {
        j = rand() % i;
        cout << "j == " << j << endl;
        std::swap(vec[j], vec[i]);
    }

    print_vector(vec);
    cout << vec.size();

}

void test_deck_subscript()
{
    Deck my_deck;
    cout << endl;
    cout << my_deck[51];
}

void test_move_vector()
{
    vector<int> a = {1, 2, 3, 4, 5};
    vector<int> b;

    print_vector(a);
    print_vector(b);

    std::move(a.begin(), a.begin()+1, back_inserter(b));

    cerr << "a has: " << a.size() << endl;
    cerr << "b has: " << b.size() << endl;

    a.erase(a.begin(), a.begin()+1);

    print_vector(a);
    print_vector(b);

    cerr << "a has: " << a.size() << endl;
    cerr << "b has: " << b.size() << endl;
}

void test_poker_hand_push_back()
{
    Poker_Hand hand;
    hand.push_back(Card(2,1));
    hand.push_back(Card(3,2));
    hand.push_back(Card(4,3));
    cout << hand << endl;

    Player player1(1);
    player1.add_card(Card(2,1));
    player1.add_card(Card(2,2));
    player1.reveal_cards();

}


void test_poker_hand_emplace()
{
    // by correctly reserving and emplacing, no more calls to Card's copy constructor
    Poker_Hand hand;
    hand.emplace(Card(2,1));
    hand.emplace(Card(3,2));
    hand.emplace(Card(4,3));
    cout << hand << endl;

    Player player1(1);
    player1.add_card(Card(2,1));
    player1.add_card(Card(2,2));
    player1.reveal_cards();
}

void test_emplace_vector()
{
    vector<int> vec;
    vec.reserve(52);
    cerr << "vec.size() == " << vec.size() << endl;

}


void make_move_design()
{
    bool quit = false;  // I like to initialize every Boolean variable. By
    char choice;        // initializing this one to false assumes the
    // user is not quiting.
    do
    {
        cout << "\t\tAnimal Sounds" << endl;
        cout << "\t1. Dog" << endl
             << "\t2. Dog" << endl
             << "\t3. Cow" << endl <<endl;
        cout<<"\t\tYour choice: ";
        cin>>choice;

        switch (choice)
        {
            case '1':
            case 'p':
                cout<<"Oink";
                break;
            case '2':
            case 'd':
                cout<<"Bark";
                break;
            case '3':
            case 'c':
                cout<<"Moooo"<<endl;
                break;
            case '4':
            case 'q':
                quit = true;
                break;
            default:
                cout<<"ERROR: Invalid input..."<<endl;
        }

    } while ( !quit );
}

void raise_design()
{
    // four people
    // 2nd person raises
    // should end at 1st person to call

    int total = 4;
    int raiser_index = 3;  // index goes 0, 1, 2, 3.
    int last_person = raiser_index - 1;

    cout << raiser_index % total -1 << " ==? " << last_person << endl;

    cout << "RAISE DESIGN" << endl;

    // goal is to somehow go 0, 1, 2, 3, 0

    int j = 0;
    do
    {
        // iterate over the first four players
        for(int i = 0; i <= 3; ++i)
        {
            cout << i << endl;

            if(j == 1 && i == 2)
            {
                break;
            }
        }

        ++j;

    } while (j < 2);

    cout << " NEW DESIGN" << endl << endl;

    int x = 0;  // player index
    int z = 1;  // round count
    do
    {
        x %= 4;  // indexes over four players (0, 1, 2, 3)

        if(x == 0) cout << "\nround == " << z << endl;  // print round at the
                                                        // start of every round

        cout << "player index == " << x << endl;

        if(z == 12 && x ==2) break;  // testing out break to call a stop at some
                                     // point in the while loop. in the actual
                                     // game this would represent stopping at
                                     // some player i who is the player preceeding
                                     // the player who placed the bet

        ++x;

        z = z + (x/4);  // increment z after all four players have had a chance

    } while (z < 20);  // stop this from going on for too long



    /*  opening betting round
     for all players
        each player must make a choice: bet or check

        if a player i has raised, then every player after i up to (and including)
        player i - 1 must respond to the raise by either: raising, calling or folding.

     for all players
        for player i_n (where n = 0, 1, 2 ... )
            if there's been a bet, choose: raise or check.
            else choose: bet or check.
        end
     if better != player i_0 (first player)
        all players i_n < better must be given a chance to respond

     OR
     begin
     int i = 0, where i is the current player index
     int raise_amount = 0;
     int last_better_index = -1;
     int n = total number of players;
     while (???not all players have made a move && bet is not settled???)
        current player index %= n
        if current player has not made a move (maybe don't need this) && last_better_index == -1
            choose : bet or check
            if current player chooses bet, set last_better_index == current player's index
                && set the raise_amount to player's bet
        else if (someone placed a bet (i.e. last_better_index != -1))
            current player chooses : raise or check
            if current player is the preceeding player to the last better && has
            decided to call or fold, then break
            else if current player raises, then store current player's index as the
            latest better and update the raise_amount to the current player's bet

        if current player index == n and last_better_index = -1, then obviously they
            all checked or folded. so break

        ++current player index
     end

     test_case:
     1. everyone checks or folds -> shoudl work
     2. player 3 places a bet -> should work
     3.

     how do i know if a particular player has settled a bet?
        - rather than testing each player on whether they settled a bet, you
            can design the program such that when a bet is placed, it will
            terminate when the option to respond comes back around to the person
            preceeding the better





     */
    // player 0 -> player 3. enter 0, return 3 somehow
    // 1 -> 0
    int num_players = 7;
    cout << abs(0 % num_players - (num_players - 1))<< endl;
    cout << abs(1 % 4 - 3)<< endl;
    cout << abs(2 % 4 - 3)<< endl;
    cout << abs(3 % 4 - 3)<< endl;


}


void remove_vector()
{
    vector<size_t> my_vec = {0, 1, 2, 3, 4, 5, 6, 7};

    size_t const winner_at = 2;

    auto new_end = std::remove_if(my_vec.begin(), my_vec.end(),
                                  [](const size_t& val)
                                  {return val != winner_at;});

    my_vec.erase(new_end, my_vec.end());

    print_vector(my_vec);

    // REMOVING ELEMENTS BY ROTATING TO BACK AND POPPPING OFF

    vector<size_t> my_vec2 = {0, 1, 2, 3, 4, 5, 6, 7};

    vector<size_t> ids = {0, 4, 5, 7};



}


void print_vector(vector<size_t>& vec)
{

    for(auto& ele : vec)
    {
        cout << ele << " ";
    }

}

void selection_design()
{
    // create a player
    Player p1(0);

    // give him cards
    p1.add_card(Card(2, 2));
    p1.add_card(Card(2, 4));
    p1.add_card(Card(3, 1));
    p1.add_card(Card(4, 1));
    p1.add_card(Card(5, 1));

    // show cards
    p1.discard_round();


}

void test_player_abc()
{
    Human human1(1);
    human1.add_card(Card(2,1));
    human1.add_card(Card(2,2)); 
    human1.print_hand();
    
    
}
