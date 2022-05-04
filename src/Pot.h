#ifndef Pot_h
#define Pot_h

#include "Player.h"

#include <ostream>
#include <stdexcept>
#include <iostream>



template <class T>

class Pot {

    friend std::ostream& operator<<(std::ostream& output, Pot& pot_object)
    {
        output << pot_object.get_value();
        return output;
    }

public:

    Pot() {}

    void add(T amount) {

        if(amount < 0)
        {
            throw std::out_of_range("Value cannot be removed from pot.");
        }

        value += amount;
    }

    T get_value() const {
        return value;
    }


    void award_pot(std::vector<Player>& players)
    {
        for(auto player : players)
        {
            player.add_money(get_value() / players.size());


            std::cout << "Player #" << player.get_number() << " earned $" <<
            get_value()/players.size() << std::endl;
        }

    }

private:
    T value{};



};

#endif /* Pot_h */
