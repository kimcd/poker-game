/**
 @file Five_Draw_Table.h
 @brief Five-card draw class definition.

 @section DESCRIPTION
 Five_Draw_Table orchestrates a game of five-card draw.

 @author Christopher Kim
 */



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
    
    /**
     @brief Minimum required players at any game.
     */
    static const size_t MIN_PLAYERS = 2;
    
    /**
     @brief Maximum allowable players is 6.
     */
    static const size_t MAX_PLAYERS = 6;
    
    /**
     @brief Default ante each player must pay to play.
    */
    static const int ANTE = 10;

    /**
     @brief Initialize the number of players at a table.
     
     Construct a five-draw game by passing the number of players at a game.
     Validates number of players.
     
     @param num_players The number of players at the game.
     */
    Five_Draw_Table(const size_t num_players);

    /**
     @brief Initialize a table.
     
     Not the recommended constructor.
     
     */
    Five_Draw_Table();

    Five_Draw_Table(const int num_bots, const size_t num_players);

    size_t prompt_players() const;

    void begin_game();

    void open_betting_round();

    void discard_round();

    std::vector<size_t> showdown_round();

    static bool debug_flag;

private:

    void print_method(const std::string& method) const;  /*!< Detailed description after the member */

    void print_pot() const;  //!< Brief description after the member

    std::vector<Player> players;

    Dealer dealer;

    size_t ante{50};

    Pot<int> pot;

    std::vector<Player> create_players(const size_t num_players) const;

    void collect_ante();
};


#endif /* Five_Draw_Table_h */
