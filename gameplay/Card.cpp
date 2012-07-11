#include "Card.h"
#include <string>
#include <cassert>
using namespace std;

namespace {
const char* suits[SUIT_COUNT] = {"C", "D", "H", "S"};
const char* ranks[RANK_COUNT] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
}

Card::Card(Suit s, Rank r){
	suit_ = s;
	rank_ = r;
}

Suit Card::getSuit() const{
	return suit_;
}

Rank Card::getRank() const{
	return rank_;
}

string Card::getRankName() const {
    return string(ranks[rank_]);
}

bool operator==(const Card &a, const Card &b){
	return a.getSuit() == b.getSuit() && a.getRank() == b.getRank();
}

ostream &operator<<(ostream &out, const Card &c){
		
	out << ranks[c.getRank()] << suits[c.getSuit()];
	
	return out;
}

istream &operator>>(istream &in, Card &c){
	const static string suitsStr = "CDHS";
	const static string ranksStr = "A234567891JQK";
	
	string str;
	in >> str;
	assert ( !in.fail() );
	
	//Read in the rank, make sure it's valid
	c.rank_ = (Rank)ranksStr.find( str.at(0) );
	assert ( c.rank_ != string::npos );
	
	//If it's a 10, make sure the 2nd character is a 0
	if ( c.rank_ == TEN ){
		assert(str.at(1) == '0');
		str.at(1) = str.at(2);
	}
	
	//Read in the suit, make sure it's valid
	c.suit_ = (Suit)suitsStr.find( str.at(1) );
	assert ( c.suit_ != string::npos );
	
	return in;
}
