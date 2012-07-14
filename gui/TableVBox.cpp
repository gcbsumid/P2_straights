/************************************************
 * TableVBox.cpp                                *
 * Author: Christian Sumido, Didier Smith       *
 ************************************************/

// Include our written code
#include "TableVBox.h"
#include "RowHBox.h"
#include "../gameplay/Card.h"

// Incude C++ Libraries
#include <iostream>
using namespace std;

class GamePlay;

// Constructor - it creates the 4 suits in a Hbox each
TableVBox::TableVBox(DeckGui* deck, GamePlay* gameplay) : 
        mGamePlay(gameplay), mPanel(false, 5), mDeck(deck) { 
    
    // Add the panel
    add(mPanel);

    for (int i = 0; i < 4; i++) {
        // adds all the new row of cards onto the panel as a child
        mSuits[i] = new RowHBox(mDeck, mGamePlay, i, 5);
        mPanel.pack_start(*mSuits[i], Gtk::PACK_SHRINK);
    }

    // The final step is to display the buttons (they display themselves)
    show_all_children();
}


// Destructor - deletes each row of cards
TableVBox::~TableVBox(){
    for (int i = 0; i < 4; i++) {
        delete mSuits[i];
    }
}

// Inserts the card being played into its proper row and column
void TableVBox::CardPlayed(Card* card) {
    mSuits[(int)card->getSuit()]->CardPlayed(card);
}

// Resets each card on the table to a blank card
void TableVBox::ClearTable() {
    for (int i = 0; i < 4; i++) {
        mSuits[i]->Reset();
    }
}
