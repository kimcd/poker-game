#include "Card.h"

#include <iostream>

#include <string>
using std::string;

#include <stdexcept>

//bool Card::debug_flag = false;

void Card::print_method(const std::string& method) const
{
    if(debug_flag)
    {
        std::cerr << "Card::" << method << std::endl;
    }

}

// copy construction
Card::Card(const Card &card_object)
{
    if(debug_flag)
    {
        std::cerr << "Card::copy() value == "
        		<< card_object.get_value()
        		<<  " suit == " << card_object.get_suit() << std::endl;
    }

    value = card_object.value;
    suit = card_object.suit;

}

Card::Card() {
    print_method("Card()");
	value = Value::EMPTY;
	suit = Suit::EMPTY;
}

Card::~Card()
{
    //cerr << "Card: " << get_value() << " " << get_suit() << " destructed" << endl;
    print_method("~Card()");
}

/**
 * Parameterized constructor.
 */
Card::Card(const Card::Value &value, const Card::Suit &suit)
: value(value), suit(suit)
{
    print_method("Card(Card::Value, Card::Suit)");
    // this->value = value;
}

// Construct by ints. This is used by Deck.
Card::Card(const int value, const int suit)
:value(int_to_card_value(value)), suit(int_to_card_suit(suit))
{
    //
}


int Card::get_value() const {
	// TODO: consider having this return Card::Value
    return static_cast<int>(value);
}


int Card::get_suit() const {
	// TODO: consider having this return Card::Suit
    return static_cast<int>(suit);
}

/* implement this instead of returning int
Card::Value Card::get_value() const {
    return value;
}

Card::Suit Card::get_suit() const {
    return suit;
}
*/


// non-member helper
Card::Value int_to_card_value(const int value)
{
    Card::Value val;

    switch (value) {
        case 2:
            val = Card::Value::TWO;
            break;
        case 3:
            val = Card::Value::THREE;
            break;
        case 4:
            val = Card::Value::FOUR;
            break;
        case 5:
            val = Card::Value::FIVE;
            break;
        case 6:
            val = Card::Value::SIX;
            break;
        case 7:
            val = Card::Value::SEVEN;
            break;
        case 8:
            val = Card::Value::EIGHT;
            break;
        case 9:
            val = Card::Value::NINE;
            break;
        case 10:
            val = Card::Value::TEN;
            break;
        case 11:
            val = Card::Value::JACK;
            break;
        case 12:
            val = Card::Value::QUEEN;
            break;
        case 13:
            val = Card::Value::KING;
            break;
        case 14:
            val = Card::Value::ACE;
            break;
        default:
            throw std::invalid_argument("Unknown enumeration value for Card::Value");
            break;

    }
    return val;

}


Card::Suit int_to_card_suit(const int value)
{
    Card::Suit val;

    switch (value) {
        case 1:
            val = Card::Suit::S;
            break;
        case 2:
            val = Card::Suit::H;
            break;
        case 3:
            val = Card::Suit::D;
            break;
        case 4:
            val = Card::Suit::C;
            break;
        default:
            throw std::invalid_argument("Unknown enumeration value for Card::Suit");
            break;

    }

    return val;
}


// keep
string convert_enum_card_value_to_string(const Card::Value& value)
{

    string val;

    switch (value)
    {
        case Card::Value::EMPTY:
            val = "EMPTY";
            break;
        case Card::Value::TWO:
            val = "2";
            break;
        case Card::Value::THREE:
            val = "3";
            break;
        case Card::Value::FOUR:
            val = "4";
            break;
        case Card::Value::FIVE:
            val = "5";
            break;
        case Card::Value::SIX:
            val = "6";
            break;
        case Card::Value::SEVEN:
            val = "7";
            break;
        case Card::Value::EIGHT:
            val = "8";
            break;
        case Card::Value::NINE:
            val = "9";
            break;
        case Card::Value::TEN:
            val = "10";
            break;
        case Card::Value::JACK:
            val = "Jack";
            break;
        case Card::Value::QUEEN:
            val = "Queen";
            break;
        case Card::Value::KING:
            val = "King";
            break;
        case Card::Value::ACE:
            val = "Ace";
            break;
        default:
            throw std::invalid_argument("Unknown enumeration value ");
    }

    return val;
}

// keep
string convert_enum_card_suit_to_string(const Card::Suit& suit)
{
    string val;

    switch (suit)
    {
        case Card::Suit::EMPTY:
            val = "Empty";
            break;
        case Card::Suit::H:
            val = "Hearts";
            break;
        case Card::Suit::S:
            val = "Spades";
            break;
        case Card::Suit::D:
            val = "Diamonds";
            break;
        case Card::Suit::C:
            val = "Clubs";
            break;
        default:
            throw std::invalid_argument("Unknown enumeration value ");
            break;
    }

    return val;
}

// keep
string convert_enum_card_suit_to_pretty(const Card::Suit& suit)
{

    string val;

    switch (suit)
    {
        case Card::Suit::EMPTY:
            val = "Empty";
            break;
        case Card::Suit::H:
            //val = "\xe2\x99\xa5";
        	val = " Hearts";
            break;
        case Card::Suit::S:
            //val = "\xE2\x99\xA0";
        	val = " Spades";
            break;
        case Card::Suit::D:
            //val = "\xE2\x99\xA6";
        	val = " Diamonds";
            break;
        case Card::Suit::C:
            //val = "\xE2\x99\xA3";
        	val = " Clubs";
            break;
        default:
            throw std::invalid_argument("Unknown enumeration value.");
            break;
    }

    return val;
}


string get_pretty_card(const Card::Value& val, const Card::Suit& suit)
{

    string pretty_string = convert_enum_card_value_to_string(val)
    + convert_enum_card_suit_to_pretty(suit);

    return pretty_string;
}


std::ostream& operator<<(std::ostream& output, const Card& card_obj)
{
    output << convert_enum_card_value_to_string(card_obj.value) << " of "
    << convert_enum_card_suit_to_string(card_obj.suit);

    return output;
}

