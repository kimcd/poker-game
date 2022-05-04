#ifndef Card_h
#define Card_h

#include <ostream>
#include <string>

class Card {

    // use a const reference, so as not to make copies when streaming see
    // poker_hand overloaded operator<<
    friend std::ostream& operator<<(std::ostream&, const Card& card_obj);

public:
	enum class Value {
		EMPTY = -1,  // consider deleting
		TWO = 2,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING,
		ACE};

    enum class Suit {
        EMPTY = -1,  // consider deleting
        S = 1,
        H = 2,
        D = 3,
        C = 4
    };

    Card();

    ~Card();

    Card(const Card::Value &value, const Card::Suit &suit);

    Card(const int value, const int suit);

    Card(const Card &card_object);


    inline Card::Value get_value_enum() const
    {
        return value;
    }

    inline Card::Suit get_suit_enum() const
    {
        return suit;
    }

    //Card::Value get_value() const;

    //Card::Suit get_suit() const;



    // queue for deletion
    int get_suit() const;  // return as int
    int get_value() const;  // return as int
    void print_value() const;
    void print_value(const Card::Value &value) const;
    void print_suit() const;
    static bool debug_flag;
private:

    void print_method(const std::string& method) const;

    Card::Value value;
    Card::Suit suit;

};

// FREE FUNCTIONS

/*
 * @brief Free function to print Card::Value to screen.
 */
void print_enum_card_value(Card::Value& value);


/*
 * @brief Free function to print Card::Suit to screen.
 */
void print_enum_card_suit(Card::Suit& suit);

std::string get_pretty_card(const Card::Value& val, const Card::Suit& suit);
std::string convert_enum_card_suit_to_pretty(const Card::Suit& suit);


Card::Value int_to_card_value(const int value);
Card::Suit int_to_card_suit(const int value);

std::string convert_enum_card_value_to_string(const Card::Value& value);
std::string convert_enum_card_suit_to_string(const Card::Suit& suit);




#endif /* Card_h */
