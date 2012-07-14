/************************************************
 * RowHBox.cpp                                *
 * Author: Christian Sumido, Didier Smith       *
 ************************************************/

// Includes our written code
#include "RowHBox.h"
#include "CardPics.h"
#include "DeckGui.h"
#include "../gameplay/Card.h"


// Includes Gtkmm Libraries
#include <gtkmm/box.h>
#include <gtkmm/button.h>

// Include C++ Libraries
#include <iostream> 

using namespace std;

// Constructor - it creates the 4 suits in a Hbox each
RowHBox::RowHBox(DeckGui* deck, GamePlay* gameplay, int suit, int spacing = 5)
        : HBox(true, spacing), mSuit(suit), mGamePlay(gameplay), mDeck(deck) {
    
    // Create the 13 card slots
    for (int i = 0; i < 13; i++) {
        // First make them empty slots
        mCards[i] = new CardPics(false, mDeck, mGamePlay, RANK_COUNT, SUIT_COUNT);
        
        // add them to the Hbox
        pack_start(*mCards[i]);
    }

    // The final step is to display the cards (they display themselves)
    show_all_children();

}

// Destructor - Deletes the each card object
RowHBox::~RowHBox() {
    for (int i = 0; i < 13; i++) {
        delete mCards[i];
    }
}

// Adds card to itsp ropper slot
void RowHBox::CardPlayed(Card* card) {
    // Updates card image in proper slot
    mCards[(int)card->getRank()]->UpdateCard(card->getRank(), card->getSuit());
}

// Resets the entire array of cards to blank cards
void RowHBox::Reset() {
    for (int i = 0; i < 13; i++) {
        // Removes the card image and replaces it as the blank card
        mCards[i]->RemoveCard();
    }
}
