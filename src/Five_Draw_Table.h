#ifndef Five_Draw_Table_h
#define Five_Draw_Table_h

#include "Player.h"
#include "Dealer.h"
#include "Pot.h"

#include <vector>
#include <string>

class Five_Draw_Table
{
public:

    static const size_t MIN_PLAYERS = 2;
    static const size_t MAX_PLAYERS = 6;
    static const int ANTE = 10;

    //
    Five_Draw_Table(const size_t num_players);

    // Provide default construction when prompting for num_players input.
    Five_Draw_Table();

    Five_Draw_Table(const int num_bots, const size_t num_players);

    size_t prompt_players() const;

    void begin_game();

    void open_betting_round();

    void discard_round();

    std::vector<size_t> showdown_round();

    static bool debug_flag;

private:

    void print_method(const std::string& method) const;

    void print_pot() const;

    std::vector<Player> players;

    Dealer dealer;

    size_t ante{50};

    Pot<int> pot;

    std::vector<Player> create_players(const size_t num_players) const;

    void collect_ante();
};


#endif /* Five_Draw_Table_h */
