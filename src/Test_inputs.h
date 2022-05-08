/*
 * Test_inputs.h
 *
 *  Created on: Apr 22, 2022
 *      Author: kimcd1
 */

#ifndef TEST_INPUTS_H_
#define TEST_INPUTS_H_

#include "Card.h"
/*
void string_to_hand(const array<string, 5> &hand1, const array<string, 5> &hand2);
Card::Value char_to_value(const char &value);
Card::Suit char_to_suit(const char &value);

// Convert a char input to corresponding Card::Value.
Card::Value char_to_value(const char &value) {
	switch(value) {
	case '2':
		return Card::Value::TWO;
	case '3':
		return Card::Value::THREE;
	case '4':
		return Card::Value::FOUR;
	case '5':
		return Card::Value::FIVE;
	case '6':
		return Card::Value::SIX;
	case '7':
		return Card::Value::SEVEN;
	case '8':
		return Card::Value::EIGHT;
	case '9':
		return Card::Value::NINE;
	case '0':
	case 'T':
	case 't':
		return Card::Value::TEN;
	case 'J':
	case 'j':
		return Card::Value::JACK;
	case 'Q':
	case 'q':
		return Card::Value::QUEEN;
	case 'K':
	case 'k':
		return Card::Value::KING;
	case 'A':
	case 'a':
		return Card::Value::ACE;
	default :
		return Card::Value::EMPTY;
	}
}

// Convert a char input to corresponding Card::Suit.
Card::Suit char_to_suit(const char &value) {
	switch(value) {
		case 'S':
		case 's':
			return Card::Suit::S;
		case 'H':
		case 'h':
			return Card::Suit::H;
		case 'D':
		case 'd':
			return Card::Suit::D;
		case 'C':
		case 'c':
			return Card::Suit::C;
		default :
			return Card::Suit::EMPTY;
		}
}


// Convert string to Hand
void string_to_hand(const array<string, 5> &hand1, const array<string, 5> &hand2) {
	Card card1(char_to_value(hand1[0].at(0)), char_to_suit(hand1[0].at(1)));
	Card card2(char_to_value(hand1[1].at(0)), char_to_suit(hand1[1].at(1)));
	Card card3(char_to_value(hand1[2].at(0)), char_to_suit(hand1[2].at(1)));
	Card card4(char_to_value(hand1[3].at(0)), char_to_suit(hand1[3].at(1)));
	Card card5(char_to_value(hand1[4].at(0)), char_to_suit(hand1[4].at(1)));

	Card card6(char_to_value(hand2[0].at(0)), char_to_suit(hand2[0].at(1)));
	Card card7(char_to_value(hand2[1].at(0)), char_to_suit(hand2[1].at(1)));
	Card card8(char_to_value(hand2[2].at(0)), char_to_suit(hand2[2].at(1)));
	Card card9(char_to_value(hand2[3].at(0)), char_to_suit(hand2[3].at(1)));
	Card card10(char_to_value(hand2[4].at(0)), char_to_suit(hand2[4].at(1)));

	Hand my_hand1(card1, card2, card3, card4, card5);
	//my_hand1.set_unique_values();
	//my_hand1.set_unique_values_frequency();
	//my_hand1.set_sorted_unique();
	//my_hand1.set_hand_type();


	Hand my_hand2(card6, card7, card8, card9, card10);
	//my_hand2.set_unique_values();
	//my_hand2.set_unique_values_frequency();
	//my_hand2.set_sorted_unique();
	//my_hand2.set_hand_type();

	cout << "______________________________________________________________________________" << endl;

	// Print hand report.
	my_hand1.print_hand_report();
	my_hand2.print_hand_report();

	// Send to Hand_rank to compare hands.
	Hand_rank my_rank(my_hand1, my_hand2);
	my_rank.print_outcome();

}


// STRAIGH FLUSH  ///////////////////////////////////////
	array<string, 5> hand1 = {"Tc", "9c", "8c", "7c", "6c"};
	array<string, 5> hand2 = {"8h", "7h", "6h", "5h", "4h"};
	string_to_hand(hand1, hand2);

	array<string, 5> hand3 = {"8h", "7h", "6h", "5h", "4h"};
	array<string, 5> hand4 = {"6s", "5s", "4s", "3s", "2s"};
	string_to_hand(hand3, hand4);

	array<string, 5> hand5 = {"7d", "6d", "5d", "4d", "3d"};
	array<string, 5> hand6 = {"7s", "6s", "5s", "4s", "3s"};
	string_to_hand(hand5, hand6);

	// FOUR OF A KIND  ///////////////////////////////////////
	array<string, 5> hand7 = {"ks", "kh", "kd", "ks", "3h"};
	array<string, 5> hand8 = {"7h", "7d", "7s", "7c", "qh"};
	string_to_hand(hand7, hand8);

	array<string, 5> hand9 = {"7s", "7h", "7d", "7s", "qh"};
	array<string, 5> hand10 = {"7h", "7d", "7s", "7c", "0s"};
	string_to_hand(hand9, hand10);

	array<string, 5> hand11 = {"4c", "4s", "4d", "4h", "9c"};
	array<string, 5> hand12 = {"4d", "4s", "4c", "4h", "9d"};
	string_to_hand(hand11, hand12);

	// FULL HOUSE ///////////////////////////////////////
	array<string, 5> hand13 = {"8s", "8d", "8h", "7d", "7s"};
	array<string, 5> hand14 = {"4d", "4s", "4c", "9s", "9c"};
	string_to_hand(hand13, hand14);

	array<string, 5> hand15 = {"4d", "4s", "4c", "9s", "9c"};
	array<string, 5> hand16 = {"4d", "4s", "4c", "5s", "5d"};
	string_to_hand(hand15, hand16);

	array<string, 5> hand17 = {"kd", "ks", "kc", "js", "jc"};
	array<string, 5> hand18 = {"kc", "kh", "kd", "jc", "jh"};
	string_to_hand(hand17, hand18);


	// FLUSH  ///////////////////////////////////////
	array<string, 5> hand65 = {"kd", "jd", "9d", "6d", "4d"};
	array<string, 5> hand66 = {"qc", "jc", "7c", "6c", "5c"};
	string_to_hand(hand65, hand66);

	array<string, 5> hand67 = {"qc", "jc", "7c", "6c", "5c"};
	array<string, 5> hand68 = {"jh", "th", "9h", "4h", "2h"};
	string_to_hand(hand67, hand68);

	array<string, 5> hand69 = {"jh", "th", "9h", "4h", "2h"};
	array<string, 5> hand70 = {"js", "ts", "8s", "6s", "3s"};
	string_to_hand(hand69, hand70);

	array<string, 5> hand71 = {"js", "ts", "8s", "6s", "3s"};
	array<string, 5> hand72 = {"jh", "th", "8h", "4h", "3h"};
	string_to_hand(hand71, hand72);

	array<string, 5> hand73 = {"jh", "th", "8h", "4h", "3h"};
	array<string, 5> hand74 = {"jc", "tc", "8c", "4c", "2c"};
	string_to_hand(hand73, hand74);

	array<string, 5> hand75 = {"td", "8d", "7d", "6d", "5d"};
	array<string, 5> hand76 = {"ts", "8s", "7s", "6s", "5s"};
	string_to_hand(hand75, hand76);

	// STRAIGHT ///////////////////////////////////////
	array<string, 5> hand19 = {"JH", "th", "9c", "8s", "7h"};
	array<string, 5> hand20 = {"ts", "9s", "8c", "7h", "6s"};
	string_to_hand(hand19, hand20);

	array<string, 5> hand21 = {"ts", "9s", "8c", "7h", "6s"};
	array<string, 5> hand22 = {"6s", "5s", "4h", "3s", "2d"};
	string_to_hand(hand21, hand22);

	array<string, 5> hand23 = {"9c", "8c", "7c", "6d", "5d"};
	array<string, 5> hand24 = {"9s", "8s", "7s", "6h", "5h"};
	string_to_hand(hand23, hand24);


	// THREE OF KIND ///////////////////////////////////////
	array<string, 5> hand25 = {"6h", "6d", "6s", "Qc", "4s"};
	array<string, 5> hand26 = {"3d", "3s", "3c", "ks", "2s"};
	string_to_hand(hand25, hand26);

	array<string, 5> hand27 = {"3d", "3s", "3c", "ks", "2s"};
	array<string, 5> hand28 = {"3d", "3s", "3c", "jc", "7h"};
	string_to_hand(hand27, hand28);

	array<string, 5> hand29 = {"3d", "3s", "3c", "jc", "7h"};
	array<string, 5> hand30 = {"3d", "3s", "3c", "js", "5d"};
	string_to_hand(hand29, hand30);

	array<string, 5> hand31 = {"9s", "9h", "9d", "td", "8h"};
	array<string, 5> hand32 = {"9c", "9s", "9d", "td", "8h"};
	string_to_hand(hand31, hand32);


	// TWO PAIR ///////////////////////////////////////
	array<string, 5> hand33 = {"0d", "0s", "2s", "2c", "Ks"};
	array<string, 5> hand34 = {"5c", "5s", "4d", "4h", "0h"};
	string_to_hand(hand33, hand34);

	array<string, 5> hand35 = {"5c", "5s", "4d", "4h", "0h"};
	array<string, 5> hand36 = {"5c", "5s", "3c", "3d", "qs"};
	string_to_hand(hand35, hand36);

	array<string, 5> hand37 = {"5c", "5s", "3c", "3d", "qs"};
	array<string, 5> hand38 = {"5c", "5s", "3c", "3d", "js"};
	string_to_hand(hand37, hand38);

	array<string, 5> hand39 = {"kd", "ks", "7d", "7h", "8h"};
	array<string, 5> hand40 = {"kc", "ks", "7c", "7h", "8c"};
	string_to_hand(hand39, hand40);

	// ONE PAIR ///////////////////////////////////////
	array<string, 5> hand41 = {"9c", "9d", "qs", "jh", "5h"};
	array<string, 5> hand42 = {"6d", "6h", "ks", "7h", "4c"};
	string_to_hand(hand41, hand42);

	array<string, 5> hand43 = {"6d", "6h", "ks", "7h", "4c"};
	array<string, 5> hand44 = {"6d", "6h", "qh", "js", "2c"};
	string_to_hand(hand43, hand44);

	array<string, 5> hand45 = {"6d", "6h", "ks", "7h", "4c"};
	array<string, 5> hand46 = {"6d", "6h", "qh", "js", "2c"};
	string_to_hand(hand45, hand46);

	array<string, 5> hand47 = {"6d", "6h", "qh", "js", "2c"};
	array<string, 5> hand48 = {"6d", "6h", "qs", "8c", "7d"};
	string_to_hand(hand47, hand48);

	array<string, 5> hand49 = {"6d", "6h", "qs", "8c", "7d"};
	array<string, 5> hand50 = {"6d", "6h", "qd", "8h", "3s"};
	string_to_hand(hand49, hand50);

	array<string, 5> hand51 = {"8d", "8h", "0h", "6c", "5s"};
	array<string, 5> hand52 = {"8h", "8c", "0c", "6s", "5c"};
	string_to_hand(hand51, hand52);

	// HIGH CARD ///////////////////////////////////////
	array<string, 5> hand53 = {"ks", "6c", "5h", "3d", "2c"};
	array<string, 5> hand54 = {"qs", "jd", "6c", "5h", "3c"};
	string_to_hand(hand53, hand54);

	array<string, 5> hand55 = {"qs", "jd", "6c", "5h", "3c"};
	array<string, 5> hand56 = {"qs", "td", "8c", "7h", "4s"};
	string_to_hand(hand55, hand56);

	array<string, 5> hand57 = {"qs", "td", "8c", "7h", "4s"};
	array<string, 5> hand58 = {"qh", "th", "7c", "6h", "4s"};
	string_to_hand(hand57, hand58);

	array<string, 5> hand59 = {"qh", "th", "7c", "6h", "4s"};
	array<string, 5> hand60 = {"qc", "tc", "7d", "5c", "4d"};
	string_to_hand(hand59, hand60);

	array<string, 5> hand61 = {"qc", "tc", "7d", "5c", "4d"};
	array<string, 5> hand62 = {"qh", "td", "7s", "5s", "2h"};
	string_to_hand(hand61, hand62);

	array<string, 5> hand63 = {"tc", "8s", "7s", "6c", "4d"};
	array<string, 5> hand64 = {"td", "8d", "7s", "6c", "4c"};
	string_to_hand(hand63, hand64);

*/


#endif /* TEST_INPUTS_H_ */
