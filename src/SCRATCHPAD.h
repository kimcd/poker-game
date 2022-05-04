//
//  SCRATCHPAD.h
//  module_12
//
//  Created by Christopher Kim on 4/22/22.
//  Copyright © 2022 Christopher Kim. All rights reserved.
//


#include "Card.h"

#include <map>
#include <vector>


#ifndef SCRATCHPAD_h
#define SCRATCHPAD_h

void test_unique_values_map();

void print_map(std::map<int, int>& map_obj);

void print_map(std::map<int, size_t>& map_obj);

void iter_enum();

void test_card();

void deck_design();

void print_deck(std::vector<Card>& deck);

void test_deck();

void print_vector(const std::vector<int>& vec);

void test_card_unique();

void test_pot();

void test_unseeded_rand();

void shuffle_design();

void test_deck_subscript();

void test_move_vector();

void test_poker_hand_push_back();

void test_poker_hand_emplace();

void test_emplace_vector();

void make_move_design();

void make_move_design2();

void raise_design();

void selection_design();

void test_card_unique_values();

void test_hand_typer();

void rank_design();

void test_multi_map_tie_breaker();

void print_multimap(std::multimap< size_t, int, std::greater<size_t> >& mm);

void remove_vector();

void print_vector(std::vector<size_t>& vec);

#endif /* SCRATCHPAD_h */
