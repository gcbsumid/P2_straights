/* To ensure that the your cards are ordered the same way as
the given program, use this shuffling algorithm.

CARD_COUNT is the constant 52
cards_ is an array of pointers to cards
*/
#include <stdlib.h>
#include "Gameplay.h"

void shuffle(Card* cards_){
	int n = Gameplay::CARD_COUNT;

	while ( n > 1 ) {
		int k = (int) (rand() % n);
		--n;
		Card c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
}
