

#include "Player.h"

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;
using std::cin;

#include <iomanip>
using std::setw;
using std::left;
using std::right;

#include <vector>
using std::vector;

#include <string>
using std::string;

#include <stdexcept>

//bool Player::debug_flag = true;

void Player::print_method(const string& method) const
{
    if(debug_flag)
    {
        cerr << "Player::" << method << endl;
    }

}


Player::Player(size_t number)
: player_number(number)
{
    print_method("Player(size_t number)");
}


Player::~Player()
{
    print_method("~Player()");
}


void Player::add_card(const Card& card)
{
    print_method("add_card(Card card)");
    hand.emplace(card);
}

Player::Move Player::pay_ante(int ante)
{

	char response;

	cout << "Player #" << player_number
    		<< " ante is $" << ante << ". [y/n]" << endl;

	cin >> response;

    switch(response)
    {
    	case 'y': case 'Y':
    		debit_money(ante);
    		return Player::Move::IN;
    		break;
		case 'n': case 'N':
			return fold();
    		break;
		default:
			throw std::invalid_argument("Unknown enumeration value ");
			break;
    }
}


// for debugging only
void Player::reveal_cards()
{
	if(debug_flag)
	{
		cerr << "Player #" << player_number << "'s hand: " << hand << endl;
	}
}


// use this when a bet has been made
Player::Move Player::raise_or_call(int& amount)
{
    int choice;
    Player::Move state = Move::NOTYET;
    bool valid_input = false;

    do
    {
        // amount is too much
        if(amount > stack)
        {
            cout << "Player #" << player_number << " you don't have enough to continue. " << endl;
            cout << "You must fold [0]." << endl;
            cin >> choice;

            switch(choice)
            {
                case 0:
                    state = fold();
                    valid_input = true;
                    break;
                default:
                    cerr << "Invalid input, try again." << endl;
                    valid_input = false;
                    break;
            }  // end switch #1
        } else if(amount == stack)
        {
            cout << "Player #" << player_number << " you can only fold or call. " << endl;
            cout << "Fold [0], Call [1]." << endl;
            cin >> choice;

            switch(choice)
            {
                case 0:
                    state = fold();
                    valid_input = true;
                    break;
                case 1:
                    state = call(amount);
                    valid_input = true;
                    break;
                default:
                    cerr << "Invalid input, try again." << endl;
                    valid_input = false;
                    break;
            }  // end switch #2
        } else
        {
            cout << "Player #" << player_number << " select your move: " << endl;
            cout << "Fold [0], Call [1], Raise [2], All-in [3]: " << endl;
            cin >> choice;

            switch(choice)
            {
                case 0:
                    state = fold();
                    valid_input = true;
                    break;
                case 1:
                    state = Player::Move::CALL;
                    valid_input = true;
                    break;
                case 2:
                    state = raise(amount);
                    valid_input = true;
                    break;
                    // add case 3 for allin
                default:
                    cerr << "Invalid input, try again." << endl;
                    valid_input = false;
                    break;
            }  // end switch #3
        }  // end else
    } while(!valid_input);  // end do

    return state;
}  // end raise_or_call


// use this when no one has placed a bet
Player::Move Player::bet_or_check(int &amount) // maybe pass a state flag if someone called
{
    int choice;
    Player::Move state = Move::NOTYET;  // initialize this (don't think i need to)
    bool valid_input = false;

    do
    {
        cout << "Player #" << player_number << " select your move: " << endl;
        cout << "Fold [0], Check [1], Place a bet [2], All-in [3]: " << endl;
        cin >> choice;

        switch(choice)
        {

            case 0:
                state = fold();
                valid_input = true;
                break;
            case 1:
                state = Player::Move::CHECK;
                valid_input = true;
                break;
            case 2:
                state = bet(amount);
                valid_input = true;
                break;
            default:
                cerr << "Invalid input, try again." << endl;
                break;
        }  // end switch

    } while(!valid_input);  // end do

    return state;
}  // end bet_or_check


Player::Move Player::call(int& amount)
{
    stack -= amount;
    return Move::CALL;
}


Player::Move Player::raise(int &amount)
{
    bool valid_amount;

    stack -= amount;  // deduct the call amount first.

    do
    {
        cout << "Player #" << player_number
        		<< " how much do you want to raise: " << endl;
        cin >> amount;  // this will reset the amount. so pot won't add called amount

        if(amount <= stack && stack != 0)
        {
            valid_amount = true;
            stack -= amount;
        } else if (amount <= 0)
        {
            cerr << "This is not a valid amount." << endl;
            valid_amount = false;
        } else if (stack == 0 )
        {
            cerr << "You are broke. Forcing fold." << endl;
            valid_amount = true;
        } else
        {
            cout << "Bet exceeds your stack of " << stack << " chips." << endl;
            valid_amount = false;
        }

    } while(!valid_amount);

    return Move::RAISE;
}


Player::Move Player::bet(int &amount)
{
    bool valid_amount;

    do
    {

        cout << "Player #" << player_number
        		<< " how much do you want to bet: " << endl;

        cin >> amount;  // this overwrites &amount

        if(amount <= stack && stack != 0)
        {
            valid_amount = true;
            stack -= amount;
        } else if (amount <= 0)
        {
            cerr << "This is not a valid amount." << endl;
            valid_amount = false;
        } else if (stack == 0)
        {
            cerr << "You have no money. Forcing fold." << endl;
            valid_amount = true;
        } else
        {
            cout << "Bet exceeds your stack of " << stack << " chips." << endl;
            valid_amount = false;
        }

    } while(!valid_amount);

    return Move::BET;

}


void Player::discard(int input)
{
    bool valid_input;

    do
    {
        switch(input)
        {
            case 0:
                hand.delete_card_at(0);
                valid_input = true;
                break;
            case 1:
                hand.delete_card_at(1);
                valid_input = true;
                break;
            case 2:
                hand.delete_card_at(2);
                valid_input = true;
                break;
            case 3:
                hand.delete_card_at(3);
                valid_input = true;
                break;
            case 4:
                hand.delete_card_at(4);
                valid_input = true;
                break;
            default:
                cerr << "Invalid input, try again." << endl;
                valid_input = false;
                break;
        }  // end switch
    } while(!valid_input);

}  // end delete_query


void Player::discard_round()
{
    int user_input;

    bool done_flag = false;

    size_t counter = 0;

    do
    {
        cout << "Player #" << player_number
        		<< " select cards to delete or [5] to keep:" << endl;

        hand_display_selection_mode();

        cin >> user_input;

        if(user_input != 5)
        {
            discard(user_input);

            ++counter;

        } else done_flag = true;

        if(counter >= Poker_Hand::MAX_CARDS) done_flag = true;

    } while(!done_flag);

}  // end discard_round


void Player::hand_display_selection_mode()
{
    vector<string> pretty_hand = hand.get_pretty_hand();

    cout << setw(15) << "[0]"
    		<< setw(15) << "[1]"
			<<setw(15) <<  "[2]"
			<<setw(15) <<  "[3]"
			<<setw(15) <<  "[4]" << endl;

    for(auto& card : pretty_hand)
    {
        cout << setw(15) << right << card;  // i think the suit symbols need 2 more than a char??
    }

    cout << endl;
}


Player::Move Player::fold()
{
    fold_flag = true;
    return Player::Move::FOLD;
}

